#include <avr/io.h>
#include <util/delay.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

char morse[] = {
    0b00010010, 0b11100100, 0b10100100, 0b01100011, 0b00010001, 0b10110100,
    0b01000011, 0b11110100, 0b00110010, 0b00010100, 0b00100011, 0b11010100,
    0b00000010, 0b00100010, 0b00000011, 0b10010100, 0b01000100, 0b01010011,
    0b01110011, 0b00000001, 0b00110011, 0b01110100, 0b00010011, 0b01100100,
    0b00100100, 0b11000100,
};

void send_morse(int letter) {
  int length = morse[letter] & 0xF;
  int bits = (morse[letter] & 0xF0) >> 4;
  for (int i = 0; i < length; i++) {
    if (bits & 0b1) {
      // krotkie
    } else {
      // dlugie
    }

    bits = bits >> 1;
  }
}

int main() {
  LED_DDR |= _BV(LED);
  while (1) {
    LED_PORT |= _BV(LED);
    _delay_ms(1000);
    LED_PORT &= ~_BV(LED);
    _delay_ms(1000);
  }
}
