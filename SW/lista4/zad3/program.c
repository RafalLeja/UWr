#include "table.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>

#define RED_PIN PB2
#define RED_VAL OCR1B
#define GREEN_PIN PB1
#define GREEN_VAL OCR1A
#define BLUE_PIN PB3
#define BLUE_VAL OCR2A

#define LED_DDR DDRB
#define LED_PORT PORTB

#define STEPS 64

struct RGB {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

void init_rgb() {
  /* timer 1:
   * FastPWM 8 bit
   * non-inverting mode
   * prescaler 8
   */
  // TCCR1A = _BV(COM1A1) | _BV(COM1A0) | _BV(COM1B1) | _BV(COM1B0) |
  // _BV(WGM10);
  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
  TCCR1B = _BV(WGM12) | _BV(CS11);

  /* timer 2:
   * FastPWM 8 bit
   * non-inverting mode
   * prescaler 8
   */
  // TCCR2A = _BV(COM2A1) | _BV(COM2A0) | _BV(WGM21) | _BV(WGM20);
  TCCR2A = _BV(COM2A1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);
}

void set_rgb(struct RGB color) {
  RED_VAL = 255 - color.red;
  GREEN_VAL = 255 - color.green;
  BLUE_VAL = 255 - color.blue;
  // RED_VAL = 255 - pgm_read_byte(&exp_table[color.red]);
  // GREEN_VAL = 255 - pgm_read_byte(&exp_table[color.green]);
  // BLUE_VAL = 255 - pgm_read_byte(&exp_table[color.blue]);
}

void breathe(struct RGB color) {
  struct RGB curr = {0, 0, 0};
  for (int i = 0; i < sizeof(brightness); i++) {
    uint8_t b = pgm_read_byte(&brightness[i]);
    curr.red = ((uint16_t)color.red * b) / 255;
    curr.green = ((uint16_t)color.green * b) / 255;
    curr.blue = ((uint16_t)color.blue * b) / 255;
    set_rgb(curr);
    _delay_ms(50);
  }
}

struct RGB hsv_to_rgb(uint8_t h) {
  uint8_t region, remainder, p, q, t;
  struct RGB color;
  region = h / 43;
  remainder = (h - region * 43) * 6;

  uint8_t V = 128 + (rand() % 128);
  uint8_t S = 128 + (rand() % 128);

  p = (V * (255 - S)) >> 8;
  q = (V * (255 - ((S * remainder) >> 8))) >> 7;
  t = (V * (255 - ((S * (255 - remainder)) >> 8))) >> 7;

  switch (region) {
  case 0:
    color.red = V;
    color.green = t;
    color.blue = p;
    break;
  case 1:
    color.red = q;
    color.green = V;
    color.blue = p;
    break;
  case 2:
    color.red = p;
    color.green = V;
    color.blue = t;
    break;
  case 3:
    color.red = p;
    color.green = q;
    color.blue = V;
    break;
  case 4:
    color.red = t;
    color.green = p;
    color.blue = V;
    break;
  default:
    color.red = V;
    color.green = p;
    color.blue = q;
    break;
  }

  return color;
}

int main() {
  LED_DDR |= _BV(RED_PIN) | _BV(GREEN_PIN) | _BV(BLUE_PIN);
  init_rgb();
  struct RGB next = {0, 0, 0};
  srand(123);
  uint8_t curr_hsv = rand() % 256;
  while (1) {
    curr_hsv = rand();
    next = hsv_to_rgb(curr_hsv);
    breathe(next);
    // set_rgb((struct RGB){0, 0, 0});
    // _delay_ms(500);
  }
}
