#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>

char cbuf[100] = {0};

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PD4
#define BTN_DDR DDRD
#define BTN_PORT PORTD
#define BTN_PIN PIND

int main(int argc, char *argv[]) {
  LED_DDR |= _BV(LED);

  BTN_PORT = _BV(BTN);

  int ctr = 0;
  while (1) {
    LED_PORT |= cbuf[ctr];

    if (BTN_PIN & _BV(BTN)) {
      cbuf[ctr] |= _BV(LED);
    } else {
      cbuf[ctr] &= ~_BV(LED);
    }

    _delay_ms(10);
    LED_PORT &= ~_BV(LED);
    ctr++;
    if (ctr >= 100) {
      ctr %= 100;
    }
  }

  return 0;
}
