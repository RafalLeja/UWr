#include <avr/io.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define BAUD 9600                              // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // zgodnie ze wzorem

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

FILE uart_file;

int main() {
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // program testowy
  printf("Hello world!\r\n\r\n");
  while (1) {
    {
      int8_t a;
      int8_t b;
      printf("podaj int8_t a: \r\n");
      scanf("%hhd", &a);
      printf("podaj int8_t b: \r\n");
      scanf("%hhd", &b);
      printf("%d\r\n", a + b); // a+b int8_t
      printf("%d\r\n", a * b); // a*b int8_t
      printf("%d\r\n", a / b); // a/b int8_t
    }

    {
      int16_t a;
      int16_t b;
      printf("podaj int16_t a: \r\n");
      scanf("%d", &a);
      printf("podaj int16_t b: \r\n");
      scanf("%d", &b);
      printf("%d\r\n", a + b); // a+b int16_t
      printf("%d\r\n", a * b); // a*b int16_t
      printf("%d\r\n", a / b); // a/b int16_t
    }

    {
      int32_t a;
      int32_t b;
      printf("podaj int32_t a: \r\n");
      scanf("%ld", &a);
      printf("podaj int32_t b: \r\n");
      scanf("%ld", &b);
      printf("%ld\r\n", a + b); // a+b int32_t
      printf("%ld\r\n", a * b); // a*b int32_t
      printf("%ld\r\n", a / b); // a/b int32_t
    }

    {
      int64_t a;
      int64_t b;
      printf("podaj int64_t a: \r\n");
      scanf("%ld", &a);
      printf("podaj int64_t b: \r\n");
      scanf("%ld", &b);
      printf("%ld\r\n", a + b); // a+b int64_t
      printf("%ld\r\n", a * b); // a*b int64_t
      printf("%ld\r\n", a / b); // a/b int64_t
    }

    {
      float a;
      float b;
      printf("podaj float a: \r\n");
      scanf("%f", &a);
      printf("podaj float b: \r\n");
      scanf("%f", &b);
      printf("%f\r\n", a + b); // a+b float
      printf("%f\r\n", a * b); // a*b float
      printf("%f\r\n", a / b); // a/b float
    }
  }
}
