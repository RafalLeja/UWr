#include "uart.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

#define SAMPLE_TIME 0.5
#define X_REF 93000

volatile int16_t volts = 0;
volatile uint64_t volume = 0;

void adc_init(void) {
  ADMUX = _BV(REFS0);

  ADCSRA = _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);

  ADCSRA |= _BV(ADEN) | _BV(ADIE);
}

void timer0_init(void) {
  TCCR0A = 0;
  TCCR0B = _BV(CS01); // 8khz
  TIMSK0 = _BV(TOIE0);
}

ISR(ADC_vect) {
  uint16_t adc_value = ADC;
  volts = (adc_value * 5000L) / 1024;
  volts -= 2500;
  volts /= 10;
  volume += volts * volts;
}

ISR(TIMER0_OVF_vect) { ADCSRA |= _BV(ADSC); }

float fast_log10_0_1(float x) {
  if (x <= 0.0f)
    return -1e30f;
  if (x == 1.0f)
    return 0.0f;

  union {
    float f;
    uint32_t i;
  } u = {x};

  int e = ((u.i >> 23) & 0xFF) - 127;

  u.i = (u.i & 0x7FFFFF) | 0x3F800000;
  float m = u.f;

  float y = m - 1.0f;

  float log10_m = y * (0.43429f - 0.21715f * y);

  return log10_m + e * 0.30103f;
}

int main(void) {
  adc_init();
  timer0_init();
  uart_init();

  sei();
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = &uart_file;

  while (1) {
    uint64_t temp_volume = volume;
    temp_volume = volume / (SAMPLE_TIME * 78);
    float relative = (float)temp_volume / X_REF;
    float log = fast_log10_0_1(relative);
    // printf("Voltage: %d mV, Mean: %lu\r\n", volts, temp_volume);
    // printf("Relative: %.6f\r\n", relative);
    // printf("Log10: %f\r\n", log);
    printf("%f dBFS\r\n", (20 * log));
    volume = 0;
    _delay_ms(SAMPLE_TIME * 1000);
  }
  return 0;
}
