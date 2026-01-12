
#include "dzwiek2.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/sfr_defs.h>
#include <avr/sleep.h>
#include <stdint.h>

#define SPI_DDR DDRB
#define SPI_PORT PORTB
#define SS PB2
#define MOSI PB3
#define SCK PB5
#define SPEED 1999

volatile uint16_t ctr = 0;

void spi_init() {
  // output
  SPI_DDR = _BV(SS) | _BV(MOSI) | _BV(SCK);
  SPI_PORT |= _BV(SS);

  // enable, master, clock = 4
  SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR1);
}

void timer1_init() {
  TCCR1A = 0;                      // CTC mode
  TCCR1B = _BV(WGM12) | _BV(CS10); // prescaler = 1
  OCR1A = SPEED;                   // 16MHz / 8kHz = 2000 cycles
  TIMSK1 = _BV(OCIE1A);            // enable interrupt
}

// ISR(SPI_STC_vect) {
//   // obudz
//   SPI_PORT = _BV(SS);
// }

void send_data(uint16_t ctr) {
  uint8_t header = 0x30;
  // uint8_t data = 128;
  uint8_t data = pgm_read_byte(&dzwiek_raw[ctr]);
  uint8_t msg1 = header | ((data & 0xf0) >> 4);
  uint8_t msg2 = (data & 0xf) << 4;

  SPI_PORT &= ~_BV(SS);

  SPDR = msg1;
  while (!(SPSR & (1 << SPIF))) {
  }

  SPDR = msg2;
  while (!(SPSR & (1 << SPIF))) {
  }

  SPI_PORT |= _BV(SS);
}

ISR(TIMER1_COMPA_vect) {
  send_data(ctr);
  ctr = (ctr + 1) % dzwiek_raw_len;
}

int main() {
  spi_init();
  timer1_init();

  set_sleep_mode(SLEEP_MODE_IDLE);

  sei();

  while (1) {
    sleep_mode();
  }
  return 0;
}
