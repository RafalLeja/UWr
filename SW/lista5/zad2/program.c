#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/sleep.h>
#include <stdint.h>
#include <stdio.h>

#define BAUD 9600                              // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // zgodnie ze wzorem

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define AVG_LEN 16

// inicjalizacja UART
void uart_init() {
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream) {
  // czekaj aż transmiter gotowy
  while (!(UCSR0A & _BV(UDRE0)))
    ;
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream) {
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)))
    ;
  return UDR0;
}

// inicjalizacja ADC
void adc_init() {
  ADMUX = _BV(REFS0); // referencja AVcc
  // multiplekser na 1.1V
  ADMUX |= _BV(MUX1) | _BV(MUX2) | _BV(MUX3);
  DIDR0 = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN);                           // włącz ADC
}

FILE uart_file;

int main() {
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj ADC
  adc_init();
  // mierz napięcie

  uint16_t prev = 0;
  uint16_t var = 0;
  uint16_t i = 0;
  while (1) {
    for (i = 0; i < 4096; i++) {
      ADCSRA |= _BV(ADSC); // wykonaj konwersję
      while (!(ADCSRA & _BV(ADIF)))
        ;                  // czekaj na wynik
      ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
      uint16_t v = ADC;    // weź zmierzoną wartość (0..1023)
      // float vcc = (float)1126 / (float)v;
      var += ((v > prev) * (v - prev)) + ((v <= prev) * (prev - v));
      prev = v;
    }
    // printf("Odczytano: %.3fV, Srednia z %d: %.3f\r\n", vcc, AVG_LEN, prev);
    printf("Wariancja (aktywne czekanie): \t\t%d\r\n", var);

    set_sleep_mode(SLEEP_MODE_ADC);
    var = 0;
  }
}
