#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <inttypes.h>

#define LED PB2
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PA7
#define BTN_DDR DDRA
#define BTN_PORT PORTA
#define BTN_PIN PINA

void io_init() {
  LED_DDR |= _BV(LED);
  BTN_PORT = _BV(BTN);
}

void spi_init() {
  // ustaw piny MOSI i SCK jako wyjścia
  DDRA = _BV(DDA4) | _BV(DDA5);
  // ustaw USI w trybie trzyprzewodowym (SPI)
  USICR = _BV(USIWM0);
}

uint8_t spi_transfer(uint8_t data) {
  // załaduj dane do przesłania
  USIDR = data;
  // wyczyść flagę przerwania USI
  USISR = _BV(USIOIF);
  // póki transmisja nie została ukończona, wysyłaj impulsy zegara
  while (!(USISR & _BV(USIOIF))) {
    // wygeneruj pojedyncze zbocze zegarowe
    // zostanie wykonane 16 razy
    USICR = _BV(USIWM0) | _BV(USICS1) | _BV(USICLK) | _BV(USITC);
  }
  // zwróć otrzymane dane
  return USIDR;
}

int main() {
  spi_init();
  io_init();
  uint8_t send = 0;
  uint8_t recv = 0;
  while (1) {
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
