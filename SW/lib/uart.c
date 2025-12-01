#include "uart.h"

char t_buf[BUFFER_SIZE] = {0};
char r_buf[BUFFER_SIZE] = {0};
uint8_t t_head = 0;
uint8_t t_tail = 0;
volatile uint8_t r_head = 0;
volatile uint8_t r_tail = 0;
FILE uart_file;

void uart_init() {
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
  // ustaw interrupt przy odbiorze
  // UCSR0B |= _BV(RXCIE0);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream) {
  while (((t_head + 1) % BUFFER_SIZE) == t_tail) {
    // bufor pełny
  }
  // cli();
  t_buf[t_head] = data;
  t_head = (t_head + 1) % BUFFER_SIZE;
  // sei();
  UCSR0B |= _BV(UDRIE0); // włącz interrupt nadawania
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream) {
  UCSR0B |= _BV(RXCIE0);
  while (r_head == r_tail) {
    // puste dane
  }
  // cli();
  char data = r_buf[r_head];
  r_head = (r_head + 1) % BUFFER_SIZE;
  // sei();
  return data;
}

char uart_readline(FILE *stream, char *buf, uint8_t maxlen) {
  uint8_t len = 0;
  while (len < (maxlen - 1)) {
    char c = uart_receive(stream);
    if (c == '\r' || c == '\n') {
      uart_transmit('\r', stream);
      uart_transmit('\n', stream);
      break;
    } else if (c == '\b' || c == 127) {
      c = 0;
      if (len > 0) {
        len--;
        buf[len] = 0;
        uart_transmit('\b', stream);
        uart_transmit(' ', stream);
        uart_transmit('\b', stream);
      }
      continue;
    } else if (ECHO) {
      uart_transmit(c, stream);
    }
    buf[len++] = c;
  }
  buf[len] = 0;
  return len;
}

ISR(USART_UDRE_vect) {
  if (t_tail != t_head) {
    UDR0 = t_buf[t_tail];
    t_tail = (t_tail + 1) % BUFFER_SIZE;
  } else {
    // wyłącz interrupt nadawania
    UCSR0B &= ~_BV(UDRIE0);
  }
}

ISR(USART_RX_vect) {
  char data = UDR0;
  r_buf[r_tail] = data;
  r_tail = (r_tail + 1) % BUFFER_SIZE;
  UCSR0B &= ~_BV(RXCIE0);
}
