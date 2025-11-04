#include <avr/io.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

#define BAUD 9600                              // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // zgodnie ze wzorem

uint8_t inline add8(uint8_t a, uint8_t b) { return a + b; }

// inicjalizacja UART
void uart_init() {
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
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

void timer1_init() {
  // ustaw tryb licznika
  // WGM1  = 0000 -- normal
  // CS1   = 001  -- prescaler 1
  TCCR1B = _BV(CS10);
}
FILE uart_file;

int main() {
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj licznik
  timer1_init();
  // program testowy

  volatile uint8_t a = 123;
  volatile uint8_t b = 45;

  while (1) {
    uint8_t a1 = a;
    uint8_t b1 = b;
    uint8_t c1;

    volatile uint16_t t0 = TCNT1; // 2 cykle
    volatile uint16_t t1 = TCNT1; // 2 cykle
    uint16_t timer_const = t1 - t0;
    t0 = TCNT1;   // 2 cykle
    c1 = a1 + b1; // add8
    t1 = TCNT1;   // 2 cykle
    printf("uint8_t + = %hu: %" PRIu16 " cykli\r\n", c1, t1 - t0 - timer_const);

    t0 = TCNT1;   // 2 cykle
    c1 = a1 * c1; // add8
    t1 = TCNT1;   // 2 cykle
    printf("uint8_t * = %hu: %" PRIu16 " cykli\r\n", c1, t1 - t0 - timer_const);

    t0 = TCNT1;   // 2 cykle
    c1 = a1 / c1; // add8
    t1 = TCNT1;   // 2 cykle
    printf("uint8_t / = %hu: %" PRIu16 " cykli\r\n", c1, t1 - t0 - timer_const);

    // ---------------

    uint16_t a2 = c1;
    uint16_t b2 = b;
    uint16_t c2;

    t0 = TCNT1;   // wartość licznika przed czekaniem
    c2 = a2 + b2; // add16
    t1 = TCNT1;   // wartość licznika po czekaniu
    printf("uint16 + = %" PRIu16 ": %" PRIu16 " cykli\r\n", c2,
           t1 - t0 - timer_const);

    t0 = TCNT1;   // wartość licznika przed czekaniem
    c2 = a2 * c2; // add16
    t1 = TCNT1;   // wartość licznika po czekaniu
    printf("uint16 * = %" PRIu16 ": %" PRIu16 " cykli\r\n", c2,
           t1 - t0 - timer_const);

    t0 = TCNT1;   // wartość licznika przed czekaniem
    c2 = a2 / c2; // add16
    t1 = TCNT1;   // wartość licznika po czekaniu
    printf("uint16 / = %" PRIu16 ": %" PRIu16 " cykli\r\n", c2,
           t1 - t0 - timer_const);

    // ---------------

    uint32_t a3 = c2;
    uint32_t b3 = b;
    uint32_t c3;

    t0 = TCNT1; // wartość licznika przed czekaniem
    c3 = a3 + b3;
    t1 = TCNT1; // wartość licznika po czekaniu
    printf("uint32 + = %lu: %" PRIu16 " cykli\r\n", c3, t1 - t0 - timer_const);

    t0 = TCNT1; // wartość licznika przed czekaniem
    c3 = a3 * c3;
    t1 = TCNT1; // wartość licznika po czekaniu
    printf("uint32 * = %lu: %" PRIu16 " cykli\r\n", c3, t1 - t0 - timer_const);

    t0 = TCNT1; // wartość licznika przed czekaniem
    c3 = a3 / c3;
    t1 = TCNT1; // wartość licznika po czekaniu
    printf("uint32 / = %lu: %" PRIu16 " cykli\r\n", c3, t1 - t0 - timer_const);

    // ---------------

    uint64_t a4 = c3;
    uint64_t b4 = b;
    uint64_t c4 = 0;

    t0 = TCNT1; // wartość licznika przed czekaniem
    c4 = a4 + b4;
    t1 = TCNT1; // wartość licznika po czekaniu
    uint32_t high = (uint32_t)(c4 >> 32);
    uint32_t low = (uint32_t)c4;
    printf("uint64 + = 0x%08lX%08lX: %" PRIu16 " cykli\r\n", high, low,
           t1 - t0 - timer_const);

    t0 = TCNT1; // wartość licznika przed czekaniem
    c4 = a4 * c4;
    t1 = TCNT1; // wartość licznika po czekaniu
    high = (uint32_t)(c4 >> 32);
    low = (uint32_t)c4;
    printf("uint64 * = 0x%08lX%08lX: %" PRIu16 " cykli\r\n", high, low,
           t1 - t0 - timer_const);

    t0 = TCNT1; // wartość licznika przed czekaniem
    c4 = a4 / c4;
    t1 = TCNT1; // wartość licznika po czekaniu
    high = (uint32_t)(c4 >> 32);
    low = (uint32_t)c4;
    printf("uint64 / = 0x%08lX%08lX: %" PRIu16 " cykli\r\n", high, low,
           t1 - t0 - timer_const);

    // ---------------

    float a6 = c4;
    float b6 = b;
    float c6 = 0;

    t0 = TCNT1; // wartość licznika przed czekaniem
    c6 = a6 + b6;
    t1 = TCNT1; // wartość licznika po czekaniu
    printf("float + = %f: %" PRIu16 " cykli\r\n", c6, t1 - t0 - timer_const);

    t0 = TCNT1; // wartość licznika przed czekaniem
    c6 = a6 * c6;
    t1 = TCNT1; // wartość licznika po czekaniu
    printf("float * = %f: %" PRIu16 " cykli\r\n", c6, t1 - t0 - timer_const);

    t0 = TCNT1; // wartość licznika przed czekaniem
    c6 = a6 / c6;
    t1 = TCNT1; // wartość licznika po czekaniu
    printf("float / = %f: %" PRIu16 " cykli\r\n", c6, t1 - t0 - timer_const);

    // ---------------

    float a7 = c6;
    float b7 = b;
    float c7 = 0;

    t0 = TCNT1; // wartość licznika przed czekaniem
    c7 = a7 + b7;
    t1 = TCNT1; // wartość licznika po czekaniu
    printf("%f %" PRIu16 "\r\n", c7, t1 - t0 - timer_const);

    printf("----\r\n\r\n");
    _delay_ms(10000);
  }
}
