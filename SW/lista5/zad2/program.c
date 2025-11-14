#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

#define BAUD 9600                              // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // zgodnie ze wzorem

#define BTN PD2
#define BTN_DDR DDRD
#define BTN_PORT PORTD
#define BTN_PIN PIND

#define V_IN 5.0
#define R1 2200

volatile uint32_t last_value = 0;

void uart_init() {
  UBRR0 = UBRR_VALUE;
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

int uart_transmit(char data, FILE *stream) {
  while (!(UCSR0A & _BV(UDRE0)))
    ;
  UDR0 = data;
  return 0;
}

int uart_receive(FILE *stream) {
  while (!(UCSR0A & _BV(RXC0)))
    ;
  return UDR0;
}

void uart_wait() {
  while (!(UCSR0A & _BV(TXC0)))
    ;
}

ISR(ADC_vect) {
  uint64_t v = ADC; // v_out/v_in * 1023
  // if (v >= 1023) {
  //   last_value = UINT32_MAX;
  //   ADCSRA |= _BV(ADIF);
  //   return;
  // }
  if (v <= 0) {
    last_value = 1;
    ADCSRA |= _BV(ADIF);
    return;
  }
  uint64_t licznik = R1 * v;
  uint32_t mianownik = 1023 - v;
  uint64_t r2 = licznik / mianownik;
  if (r2 >= UINT32_MAX) {
    last_value = UINT32_MAX;
    ADCSRA |= _BV(ADIF);
    return;
  }
  last_value = r2;
  // last_value = v;
  ADCSRA |= _BV(ADIF);
}

ISR(INT0_vect) {}

void adc_init() {
  ADMUX = _BV(REFS0); // referencja AVcc
  DIDR0 = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  // ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA =
      _BV(ADEN) | _BV(ADIE) | _BV(ADATE); // włącz ADC, interrupt, auto trigger
  ADCSRB = _BV(ADTS1);                    // przerwanie zewnętrzne 0
}

void io_init() {
  BTN_PORT = _BV(BTN);             // włącz pull-up na BTN
  EICRA = _BV(ISC01) | _BV(ISC00); // zbocze rosnące
  EIMSK = _BV(INT0);               // włącz INT0
}

FILE uart_file;

int main() {
  uart_init();
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  printf("Start\r\n");

  io_init();
  adc_init();
  sei();

  while (1) {
    printf("opor = %" PRIu32 " Ohm \r\n", last_value);
    uart_wait();
    _delay_ms(500);
  }
}
