#include "./melody.h"
#include "./notes.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <util/delay.h>

#define BZR PB1
#define BZR_DDR DDRB
#define BZR_PORT PORTB

/*
 * bit 7 - 1 / 0 - przerwa / nuta
 * bity 6-5 - długość dżwięku,
 * bity 4-3 - oktawa
 * bity 2-0 - dźwięk w tonacji
 */
// C = 0
#define BPM 90
#define EIGHT_NOTE (60000 / BPM) >> 3
static const uint16_t n = 150;
// static const size_t n = sizeof(melody) / sizeof(melody[0]);
static const uint8_t major[] = {0, 2, 4, 5, 7, 9, 11};
static const uint8_t minor[] = {0, 2, 3, 5, 7, 8, 10};

void tone(int frequency) {
  if (frequency == 0) {
    TCCR1A = 0;
    TCCR1B = 0;
    return;
  }

  uint16_t top = (F_CPU / (2UL * 8 * frequency)) - 1;

  /*
   * WGM12:0 = 4 -> CTC
   * COM1A1 = 1 -> Toggle on Compare Match
   */

  TCCR1A |= _BV(COM1A0);

  /*
   * Prescaler = 8
   */
  TCCR1B = _BV(WGM12) | _BV(CS11);

  OCR1A = top;
}

void playNote(uint16_t idx) {
  uint8_t note = pgm_read_byte(&melody[idx]);
  // uint8_t dur = 4;
  uint8_t dur = 1 << ((note & 0x60) >> 5);
  uint16_t freq;
  if (note >= 0x80) {
    freq = 440;
  } else {
    // uint8_t octave = 3;
    // uint8_t noteInKey = 5;
    uint8_t octave = (note & 0x18) >> 3;
    uint8_t noteInKey = SCALE[note & 0x7];
    freq = pgm_read_u16(&notes[(octave * 12) + KEY + noteInKey]);
  }
  tone(freq);
  for (int i = 0; i < dur; i++) {
    _delay_ms(EIGHT_NOTE);
  }
}

int main(void) {
  BZR_DDR |= _BV(BZR);

  uint16_t curr = 0;
  while (1) {
    // tone(pgm_read_u16(&notes[(3 * 12) + 5]));
    playNote(curr);
    tone(0);
    _delay_ms(10);
    curr++;
    if (curr >= n) {
      curr = 0;
    }
  }
}
