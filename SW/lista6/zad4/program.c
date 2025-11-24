
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/sfr_defs.h>
#include <avr/sleep.h>
#include <stdint.h>
#include <util/delay.h>

#define SPI_DDR DDRB
#define SPI_PORT PORTB
#define OE PB2
#define LE PB1
#define MOSI PB3
#define SCK PB5

volatile uint8_t ctr = 0;
int8_t digits[] = {0b1000000, 0b1111001, 0b0100100, 0b0110000, 0b0011001,
                   0b0010010, 0b0000010, 0b1111000, 0b0000000, 0b0010000};

void spi_init() {
  // output
  SPI_DDR |= _BV(LE) | _BV(OE) | _BV(MOSI) | _BV(SCK);

  // enable, master, clock = 4
  SPCR |= _BV(SPE) | _BV(MSTR) | _BV(SPR1) | _BV(SPR0);
  SPI_PORT &= ~_BV(OE);
  SPI_PORT &= ~_BV(LE);
}

void timer1_init() {
  TCCR1A = 0;                                  // CTC mode
  TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10); // prescaler = 1
  OCR1A = 16000;        // 16MHz / 1024 = 16kHz, 16khz / 1hz = 16000
  TIMSK1 = _BV(OCIE1A); // enable interrupt
}

void send_data(uint8_t ctr) {
  SPDR = ~digits[ctr];
  // SPDR = 0x00;
  // SPDR = 0xff;
  while (!(SPSR & (1 << SPIF))) {
  }
  SPI_PORT |= _BV(LE);
  _delay_us(1);
  SPI_PORT &= ~_BV(LE);
  // _delay_us(10);
}

ISR(TIMER1_COMPA_vect) {
  send_data(ctr);
  ctr = (ctr + 1) % 10;
}

int main() {
  spi_init();
  timer1_init();

  set_sleep_mode(SLEEP_MODE_IDLE);

  sei();

  while (1) {
    // send_data(ctr);
    // _delay_ms(1000);
    // ctr = (ctr + 1) % 10;
    sleep_mode();
  }
  return 0;
}
