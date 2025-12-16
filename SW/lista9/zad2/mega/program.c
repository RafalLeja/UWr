#include <avr/io.h>

#define LED PD5
#define LED_DDR DDRD
#define LED_PORT PORTD

#define BTN PD4
#define BTN_DDR DDRD
#define BTN_PORT PORTD
#define BTN_PIN PIND

void io_init() {
  LED_DDR |= _BV(LED);
  BTN_PORT = _BV(BTN);
}

void spi_init() {
  // ustaw piny MOSI, SCK i ~SS jako wyjścia
  DDRB |= _BV(DDB4);
  // włącz SPI w trybie master z zegarem 250 kHz
  SPCR = _BV(SPE);
}

// transfer jednego bajtu
uint8_t spi_transfer(uint8_t data) {
  // rozpocznij transmisję
  SPDR = data;
  // czekaj na ukończenie transmisji
  while (!(SPSR & _BV(SPIF)))
    ;
  // wyczyść flagę przerwania
  SPSR |= _BV(SPIF);
  // zwróć otrzymane dane
  return SPDR;
}

int main() {
  spi_init();
  io_init();
  uint8_t send = 0;
  uint8_t recv = 0;
  while (1) {
    // LED_PORT |= _BV(LED);
    if (BTN_PIN & _BV(BTN)) {
      send = 1;
    } else {
      send = 0;
    }
    recv = spi_transfer(send);
    if (recv > 0) {
      LED_PORT |= _BV(LED);
    } else {
      LED_PORT &= ~_BV(LED);
    }
  }
}
