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

inline int8_t nextFrame(int8_t n) { return n ^ (n >> 1); }

int main(void) {
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  LED_DDR |= 0xFF;
  BTN_PORT |= _BV(BTN_P) | _BV(BTN_R) | _BV(BTN_N);

  int8_t n = 0;
  while (1) {
    switch (BTN_PIN) {
    case _BV(BTN_P):
      LED_PORT = nextFrame(--n);
      break;
    case _BV(BTN_R):
      n = 0;
      LED_PORT = nextFrame(n);
      break;
    case _BV(BTN_N):
      LED_PORT = nextFrame(++n);
      break;
    default:
      break;
    }
    _delay_ms(10);
  }
  return EXIT_SUCCESS;
}
