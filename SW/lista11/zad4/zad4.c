#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/sleep.h>
#include <stdint.h>
#include <util/delay.h>

#define SERVO_PIN PB1
#define SERVO_DDR DDRB
#define SERVO_PORT PORTB

#define LED_PIN PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

void timer1_init() {
  TCCR1A = _BV(WGM11) | _BV(COM1A1);            // FastPWM ICR1
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS11); // prescaler = 8
  ICR1 = 40000; // 16MHz / 8 / 40000 = 50 Hz = 20ms
  OCR1A = 2000; // 16MHz / 8 / 3000 = 1.5ms
}

void adc_init() {
  ADMUX = _BV(REFS0); // referencja AVcc
  // multiplekser na ADC6
  ADMUX |= _BV(MUX1) | _BV(MUX2);
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN) | _BV(ADIE);               // włącz ADC i interrupt
}

ISR(ADC_vect) {
  uint16_t v = ADC;
  uint16_t angle = 2000 + (v * 2); // map 0..1023 to 2000..4000
  OCR1A = angle > 4000 ? 4000 : angle;
  if (v > 512) {
    LED_PORT |= _BV(LED_PIN);
  } else {
    LED_PORT &= ~_BV(LED_PIN);
  }
}

int main() {
  DDRB |= _BV(SERVO_PIN);
  DDRB |= _BV(LED_PIN);
  adc_init();
  timer1_init();
  sei();
  set_sleep_mode(SLEEP_MODE_IDLE);
  while (1) {
    ADCSRA |= _BV(ADSC);
    sleep_mode();
    // _delay_ms(20);
  }
}
