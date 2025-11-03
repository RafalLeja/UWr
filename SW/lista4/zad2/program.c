#include "./table.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <util/delay.h>

#define LED PB1
#define LED_DDR DDRB
#define LED_PORT PORTB

#define MAXI_U 900
#define MINI_U 200

void pwm(uint16_t fill) {
  if (fill == 0) {
    TCCR1A = 0;
    TCCR1B = 0;
    return;
  }

  /*
   * WGM12:0 = 5 -> Fast PWM 10-bit
   * COM1A1 = 1 -> set on Compare Match
   */
  TCCR1A = _BV(COM1A1) | _BV(WGM11) | _BV(WGM10);

  /*
   * Prescaler = 1
   */
  TCCR1B = _BV(WGM12) | _BV(CS10);

  OCR1A = fill;
}

void adc_init() {
  ADMUX = _BV(REFS0); // referencja AVcc
  // multiplekser na ADC0
  ADMUX &= ~(_BV(MUX0) | _BV(MUX1) | _BV(MUX2) | _BV(MUX3));
  DIDR0 = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  // ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

uint16_t adc_measure() {
  ADCSRA |= _BV(ADSC); // wykonaj konwersję
  while (!(ADCSRA & _BV(ADIF)))
    ;                  // czekaj na wynik
  ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
  return ADC;          // weź zmierzoną wartość (0..1023)
}

int main(void) {
  LED_DDR |= _BV(LED);

  adc_init();

  uint16_t light_val = 0;
  uint16_t led_val = 0;
  uint16_t desired_val = 0;
  while (1) {
    pwm(0);
    light_val = adc_measure();
    if (light_val > MAXI_U)
      light_val = MAXI_U;
    if (light_val < MINI_U)
      light_val = MINI_U;
    light_val -= MINI_U;
    desired_val = pgm_read_u16(&exp_table[light_val]);
    led_val = (led_val * 7 + desired_val) / 8;

    pwm(led_val);
    // pwm(pgm_read_u16(&lin_table[(MAXI_U - MINI_U - 1) - val]));
    _delay_ms(50);
  }
}
