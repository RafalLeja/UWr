#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/sleep.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

#define BAUD 9600                              // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // zgodnie ze wzorem

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define AVG_LEN 64

uint16_t data_buffer[AVG_LEN];

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

void uart_wait() {
  while (!(UCSR0A & _BV(TXC0)))
    ;
}

// inicjalizacja ADC
void adc_init() {
  ADMUX = _BV(REFS0); // referencja AVcc
  // multiplekser na 1.1V
  ADMUX |= _BV(MUX1) | _BV(MUX2) | _BV(MUX3);
  DIDR0 = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN) | _BV(ADIE);               // włącz ADC i interrupt
}

ISR(ADC_vect) {
  // przerwanie tylko wybudza CPU ze snu
}

uint16_t variance(uint16_t avg) {
  uint16_t var = 0;
  for (uint16_t i = 0; i < AVG_LEN; i++) {
    int16_t diff = data_buffer[i] - avg;
    // printf("diff: %" PRId16 "\r\n", diff);
    var += diff * diff;
  }
  return var / 2; // / AVG_LEN;
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

  uint16_t avg = 0;
  uint16_t i = 0;
  printf("Wariancja:\t|\taktywne czekanie\t|\tnoise reduction\t|\r\n");
  while (1) {
    avg = 0;
    for (i = 0; i < AVG_LEN; i++) {
      ADCSRA |= _BV(ADSC); // wykonaj konwersję
      while (!(ADCSRA & _BV(ADIF)))
        ;                  // czekaj na wynik
      ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
      uint16_t v = ADC;    // weź zmierzoną wartość (0..1023)
      data_buffer[i] = v;
      avg += v;
    }
    avg /= AVG_LEN;

    // printf("srednia: %" PRIu16, avg);
    // uart_wait();
    // _delay_ms(100);

    uint16_t var1 = variance(avg);

    avg = 0;

    sei();
    set_sleep_mode(SLEEP_MODE_ADC);
    for (i = 0; i < AVG_LEN; i++) {
      ADCSRA |= _BV(ADSC); // wykonaj konwersję
      sleep_mode();        // uśpij CPU do zakończenia konwersji
      uint16_t v = ADC;    // weź zmierzoną wartość (0..1023)
      data_buffer[i] = v;
      avg += v;
    }
    avg /= AVG_LEN;
    _delay_ms(100);

    // printf("srednia: %" PRIu16, avg);
    // uart_wait();
    // _delay_ms(100);

    printf("\t\t\t%" PRIu16 "\t\t\t\t%" PRIu16 "\r\n", var1, variance(avg));
    cli();
    _delay_ms(2000);
  }
}
