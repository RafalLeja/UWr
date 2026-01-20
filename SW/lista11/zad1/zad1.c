#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/sleep.h>

#define MOTOR_PIN PB1
#define MOTOR_DDR DDRB
#define MOTOR_PORT PORTB

#define LED_PIN PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

void timer1_init() {
  TCCR1A = _BV(WGM11) | _BV(WGM10) | _BV(COM1A1); // PWM mode
  TCCR1B = _BV(WGM12) | _BV(CS11) | _BV(CS10);    // prescaler = 64
  OCR1A = 500;                                    // 16MHz / 64 / 500 = 500 Hz
}

void adc_init() {
  ADMUX = _BV(REFS0); // referencja AVcc
  // multiplekser na ADC6
  ADMUX |= _BV(MUX1) | _BV(MUX2);
  DIDR0 = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN) | _BV(ADIE);               // włącz ADC i interrupt
}

ISR(ADC_vect) {
  uint16_t v = ADC;
  OCR1A = 500 - (v / 4); // map 0..1023 to 500..250
  if (v > 512) {
    LED_PORT |= _BV(LED_PIN);
  } else {
    LED_PORT &= ~_BV(LED_PIN);
  }
}

int main() {
  DDRB |= _BV(MOTOR_PIN);
  DDRB |= _BV(LED_PIN);
  adc_init();
  timer1_init();
  sei();
  set_sleep_mode(SLEEP_MODE_IDLE);
  while (1) {
    ADCSRA |= _BV(ADSC);
    sleep_mode();
  }
}
