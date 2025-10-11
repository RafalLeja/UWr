#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#define LED_DDR DDRD
#define LED_PORT PORTD

char digits[] = {0b1000000, 0b1111001, 0b0100100, 0b0110000, 0b0011001,
                 0b0010010, 0b0000010, 0b1111000, 0b0000000, 0b0010000};

char cyfra = 0;

int main(void) {
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  LED_DDR = 0xFF;
  LED_PORT = 0xFF;
  while (1) {

    LED_PORT = digits[cyfra];
    cyfra = (cyfra + 1) % 10;
    _delay_ms(1000);
  }

  return EXIT_SUCCESS;
}
