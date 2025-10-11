#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>

#define LED_DDR DDRD
#define LED_PORT PORTD

#define WIDTH 5
#define TIME 50

int32_t curr = 0;
char center = 0;
char direction = 0;

void nextFrame() {
  if (curr == 0) {
    // curr = 0xF0;
    // center = 6;
    curr = (((1 << WIDTH) - 1) << 8);
    center = (WIDTH / 2) + 8;
    return;
  }
  if (center > 16 || center < 7) {
    direction = !direction;
  }
  if (direction) {
    curr = curr >> 1;
    center--;
  } else {
    curr = curr << 1;
    center++;
  }
}

int main(void) {
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  LED_DDR |= 0xFF;
  while (1) {
    nextFrame();
    LED_PORT = (curr & 0xFF00) >> 8;
    _delay_ms(TIME);
  }
  return EXIT_SUCCESS;
}
