#include "pid.h"
#include "uart.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/sleep.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

#define K_P 0.05
#define K_I 0.0
#define K_D 0.0

struct PID_DATA pidData = {0};

#define TIME_INTERVAL 8
#define INTEGRAL_RESET 50
#define SCALING_FACTOR 128

struct GLOBAL_FLAGS {
  uint8_t pidTimer : 1;
  uint8_t dummy : 7;
} gFlags = {0, 0};

#define RES_PIN PB1
#define RES_DDR DDRB
#define RES_PORT PORTB

#define LED_PIN PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

int16_t set_temp = 200;
int16_t measured_temp = 0;
int16_t prev_measured_temp = 0;
int16_t control_input = 0;

void timer1_init() {
  TCCR1A = _BV(COM1A1) | _BV(WGM11) | _BV(WGM10); // Fast 10-bit
  TCCR1B = _BV(WGM12) | _BV(CS11) | _BV(CS10);    // prescaler = 64
  OCR1A = 1000;
}

void timer2_init() {
  TCCR2B = _BV(CS22);
  TIMSK2 = _BV(TOIE2);
  TCNT2 = 0;
}

void adc_init() {
  ADMUX = _BV(REFS0) | _BV(REFS1); // referencja 1.1V
  ADMUX |= _BV(MUX1) | _BV(MUX2);  // ADC6
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 64
  ADCSRA |= _BV(ADEN) | _BV(ADATE) | _BV(ADIE);  // włącz ADC i interrupt
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
    control_input = 4 * pid_Controller(set_temp, measured_temp, &pidData);
    // pid_Controller(set_speed, motor_u, &pidData) / SCALING_FACTOR;
    if (control_input < 0)
      control_input = 0;
    if (control_input > 1023)
      control_input = 1023;
    OCR1A = control_input;
    // OCR1A = (set_temp + control_input) * 2;
    //
    //     if (integral > INTEGRAL_RESET) {
    //       integral = 0;
    //       // pid_Reset_Integrator(&pidData);
    //     } else
    //       integral++;
    //     // OCR1A = 512;
  }
}

ISR(ADC_vect) {
  LED_PORT ^= _BV(LED_PIN);
  uint16_t adc_value = ADC * 11;
  adc_value -= 5000;
  // adc_value /= 10;
  // przeliczenie wartości ADC na temperaturę w °C
  measured_temp = (adc_value / 4) + (3 * prev_measured_temp) / 4;
  prev_measured_temp = measured_temp;
  // measured_temp = (adc_value * 110) / 1023;
}

int main() {
  DDRB |= _BV(RES_PIN);
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

  printf("Sterownik PID - regulacja temperatury\r\n");
  printf("Podaj temperaturę zadaną w °C: ");
  scanf("%d", &set_temp);

  ADCSRA |= _BV(ADSC); // start konwersji ADC
  while (1) {
    _delay_ms(300);
    printf("S: %4d, M: %4d C: %4d\r\n", set_temp, measured_temp, control_input);
  }
}
