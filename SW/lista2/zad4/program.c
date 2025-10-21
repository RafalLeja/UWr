#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdlib.h>
#include <util/delay.h>

#define LED_DDR DDRD
#define LED_PORT PORTD

#define PNP0 PC0
#define PNP1 PC1
#define PNP_DDR DDRC
#define PNP_PORT PORTC
#define PNP_PIN PINC

int8_t digits[] = {0b1000000, 0b1111001, 0b0100100, 0b0110000, 0b0011001,
                   0b0010010, 0b0000010, 0b1111000, 0b0000000, 0b0010000};

int8_t czas = 0;
int8_t centy = 0;
int8_t cyfra = 0;

int main(void) {
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  LED_DDR = 0xFF;
  LED_PORT = 0xFF;

  PNP_DDR |= _BV(PNP0) | _BV(PNP1);
  PNP_PORT |= _BV(PNP0) | _BV(PNP1);

  while (1) {
    PNP_PORT |= _BV(PNP0) | _BV(PNP1);

    if (cyfra) {
      // jedności
      LED_PORT = digits[czas % 10];
      PNP_PORT &= ~_BV(PNP1);
    } else {
      // dziesiątek
      LED_PORT = digits[czas / 10];
      PNP_PORT &= ~_BV(PNP0);
    }

    cyfra = 1 - cyfra;
    centy++;
    if (centy == 100) {
      czas++;
      centy = 0;
    }
    if (czas == 60) {
      czas = 0;
    }
    _delay_ms(10);
  }

  return EXIT_SUCCESS;
}
