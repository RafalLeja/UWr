#include "pid.h"
#include "uart.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/sleep.h>
#include <stdint.h>
#include <util/delay.h>
void pot();

#define K_P 1.5
#define K_I 0.005
#define K_D 0.0

struct PID_DATA pidData;

#define TIME_INTERVAL 8
#define INTEGRAL_RESET 50
#define SCALING_FACTOR 128

struct GLOBAL_FLAGS {
  uint8_t pidTimer : 1;
  uint8_t dummy : 7;
} gFlags = {0, 0};

#define MOTOR_PIN PB1
#define MOTOR_DDR DDRB
#define MOTOR_PORT PORTB

#define LED_PIN PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define MIN_PWM 50

uint16_t motor_u = 0;
uint16_t motor_u_prev = 0;
uint16_t set_speed = 0;
uint16_t set_speed_prev = 0;
uint16_t control_input = 0;

void timer1_init() {
  TCCR1A = _BV(COM1A1);                        // Phase and Freq mode
  TCCR1B = _BV(WGM13) | _BV(CS11) | _BV(CS10); // prescaler = 256
  TIMSK1 = _BV(TOIE1);                         // overflow interrupt enable
  ICR1 = 1024;                                 // TOP value
  OCR1A = 200;
}

void timer2_init() {
  TCCR2B = _BV(CS22);
  TIMSK2 = _BV(TOIE2);
  TCNT2 = 0;
}

void adc_init() {
  ADMUX = _BV(REFS0); // referencja AVcc
  ADMUX |= _BV(MUX1);
  DIDR0 = _BV(ADC2D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 64
  ADCSRA |= _BV(ADEN);                           // włącz ADC i interrupt
}

ISR(TIMER1_OVF_vect) {
  ADMUX &= ~(_BV(MUX0) | _BV(MUX1) | _BV(MUX2) | _BV(MUX3));
  ADMUX |= _BV(MUX1); // ADC2 - pomiar napięcia na silniku
  ADCSRA |= _BV(ADSC);
  while (ADCSRA & _BV(ADSC))
    ;

  ADCSRA |= _BV(ADSC);
  while (ADCSRA & _BV(ADSC))
    ;

  motor_u = ADC; // szybko:512-1024:wolno
  motor_u -= 200;
  motor_u = (motor_u + motor_u_prev) / 2;
  motor_u_prev = motor_u;
  // motor_u = motor_u > 0 ? motor_u : 0;
  // motor_u *= 2;
  // motor_u = motor_u < 1023 ? motor_u : 1023;
  // motor_u = motor_u > 150 ? motor_u : 150;
  pot();
}

void pot() {
  ADMUX &= ~(_BV(MUX0) | _BV(MUX1) | _BV(MUX2) | _BV(MUX3));
  ADMUX |= _BV(MUX2) | _BV(MUX1); // ADC6 - pomiar potencjometru
  ADCSRA |= _BV(ADSC);
  while (ADCSRA & _BV(ADSC))
    ;

  ADCSRA |= _BV(ADSC);
  while (ADCSRA & _BV(ADSC))
    ;

  set_speed = ADC;
  set_speed = set_speed > 200 ? set_speed : 200;
  set_speed = (set_speed + set_speed_prev) / 2;
  set_speed_prev = set_speed;
  // uint32_t a = ADC * 700;
  // a /= 1023;
  // set_speed = a;
}

ISR(TIMER2_OVF_vect) {
  static uint16_t i = 0;
  static uint16_t integral;
  if (i < TIME_INTERVAL) {
    i++;
  } else {
    LED_PORT ^= _BV(LED_PIN);
    i = 0;
    //     gFlags.pidTimer = 1;
    control_input = pid_Controller(set_speed, motor_u, &pidData);
    if (control_input > 1023)
      control_input = 1023;
    else if (control_input < MIN_PWM)
      control_input = MIN_PWM;
    OCR1A = control_input;
    // OCR1A = 1024;
    //
    //     if (integral > INTEGRAL_RESET) {
    //       integral = 0;
    //       // pid_Reset_Integrator(&pidData);
    //     } else
    //       integral++;
    //     // OCR1A = 512;
  }
}

int main() {
  DDRB |= _BV(MOTOR_PIN);
  DDRB |= _BV(LED_PIN);
  adc_init();
  timer2_init();
  timer1_init();
  sei();

  uart_init();
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  pid_Init(K_P * SCALING_FACTOR, K_I * SCALING_FACTOR, K_D * SCALING_FACTOR,
           &pidData);

  while (1) {
    _delay_ms(20);
    printf("S: %4u, M: %4u C: %4u\r\n", set_speed, motor_u, control_input);
  }
}
