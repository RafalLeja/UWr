#include "pid.h"
#include "uart.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/sleep.h>
#include <stdint.h>
#include <util/delay.h>
void pot();

#define K_P 0.22
// #define K_I 0.00
#define K_I 0.008
// #define K_D 0.00
#define K_D 0.008

struct PID_DATA pidData = {0};

#define AVG_LEN 16
#define TIME_INTERVAL 4
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

#define MAX_PWM 512
#define MIN_PWM 0

int16_t motor_u = 0;
int16_t motor_u_prev = 0;
int32_t motor_u_avg = 0;
uint8_t avg_count = 0;
int16_t set_speed = 0;
int16_t set_speed_prev = 0;
int16_t control_input = 0;

void timer1_init() {
  TCCR1A = _BV(COM1A1);                        // Phase and Freq mode
  TCCR1B = _BV(WGM13) | _BV(CS11) | _BV(CS10); // prescaler = 256
  TIMSK1 = _BV(TOIE1);                         // overflow interrupt enable
  ICR1 = MAX_PWM;                              // TOP value
  OCR1A = MIN_PWM;
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

  uint16_t tmp = ADC; // szybko:512-1024:wolno
  // tmp = 512 - tmp;
  // tmp -= 70;
  // tmp *= 2;
  // tmp = tmp < 512 ? tmp : 512;
  // tmp = tmp > 0 ? tmp : 0;
  if (avg_count < AVG_LEN) {
    avg_count++;
    motor_u_avg += tmp;
  } else {
    avg_count = 0;
    // motor_u_avg += tmp;
    motor_u = motor_u_avg / AVG_LEN;
    motor_u = 1023 - motor_u;
    // motor_u -= 70;
    // motor_u *= 2;
    // motor_u = motor_u < 512 ? motor_u : 512;
    // motor_u = motor_u > 0 ? motor_u : 0;

    motor_u_avg = 0;
  }
  // motor_u = (motor_u / 4) + (3 * motor_u_prev) / 4;
  // motor_u_prev = motor_u;
  // motor_u = motor_u > 150 ? motor_u : 150;
  // motor_u *= 2;
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

  set_speed = ((int32_t)ADC * 750UL) / 1023UL;
  // set_speed = set_speed > 200 ? set_speed : 200;
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
    control_input =
        (MAX_PWM / 255) * pid_Controller(set_speed, motor_u, &pidData);
    // pid_Controller(set_speed, motor_u, &pidData) / SCALING_FACTOR;
    if (control_input < MIN_PWM)
      control_input = MIN_PWM;
    if (control_input > MAX_PWM)
      control_input = MAX_PWM;
    OCR1A = control_input;
    // OCR1A = 512;
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
    _delay_ms(200);
    printf("S: %4d, M: %4d C: %4d\r\n", set_speed, motor_u, control_input);
  }
}
