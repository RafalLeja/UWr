#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>

#define LED_DDR DDRD
#define LED_PORT PORTD

#define BTN_P PB0
#define BTN_R PB1
#define BTN_N PB2
#define BTN_DDR DDRB
#define BTN_PORT PORTB
#define BTN_PIN PINB

inline uint8_t nextFrame(uint8_t n) { return n ^ (n >> 1); }

int main(void) {
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  LED_DDR |= 0xFF;
  BTN_PORT |= _BV(BTN_P) | _BV(BTN_R) | _BV(BTN_N);

  uint8_t n = 0;
  while (1) {
    if ((BTN_PIN & _BV(BTN_P)) == 0) {
      LED_PORT = nextFrame(--n);
      _delay_ms(200);
    } else if ((BTN_PIN & _BV(BTN_R)) == 0) {
      n = 0;
      LED_PORT = nextFrame(n);
      _delay_ms(200);
    } else if ((BTN_PIN & _BV(BTN_N)) == 0) {
      LED_PORT = nextFrame(++n);
      _delay_ms(200);
    }
  }
  return EXIT_SUCCESS;
}
