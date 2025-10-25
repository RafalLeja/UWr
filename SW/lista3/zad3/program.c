#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <util/delay.h>

#define LED PB1
#define LED_DDR DDRB
#define LED_PORT PORTB

/*
 * https://ledshield.wordpress.com/2012/11/13/led-brightness-to-your-eye-gamma-correction-no/
 */
static const uint8_t exp_table[] PROGMEM = {
    0,  1,  2,  3,  4,  5,  7,   9,   12,  15,  18,  22,  27,  32,  38,  44,
    51, 58, 67, 76, 86, 96, 108, 120, 134, 148, 163, 180, 197, 216, 235, 255};

void pwm(uint8_t fill) {
  if (fill == 0) {
    TCCR1A = 0;
    TCCR1B = 0;
    return;
  }

  /*
   * WGM12:0 = 5 -> Fast PWM 8-bit
   * COM1A1 = 1 -> set on Compare Match
   */

  TCCR1A = _BV(COM1A1) | _BV(WGM10);

  /*
   * Prescaler = 8
   */
  TCCR1B = _BV(WGM12) | _BV(CS11);

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

  uint16_t val = 0;
  while (1) {
    pwm(0);
    val = (adc_measure() >> 5); // 0 - 255
    // val = 1 << val;
    pwm(pgm_read_byte(&exp_table[val]));
    _delay_ms(20);
  }
}
