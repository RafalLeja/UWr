#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <util/delay.h>

#define BAUD 9600                              // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // zgodnie ze wzorem

uint16_t times[] = {0, 0};
uint8_t idx = 0;
uint16_t freq = 0;

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
void timer_init() {
  TCCR1B = _BV(CS11);  // prescaler 8
  TIMSK1 = _BV(ICIE1); // enable input capture interrupt
}

ISR(TIMER1_CAPT_vect) {
  times[idx] = ICR1;
  // TCCR1B ^= _BV(ICES1); // toggle edge
  if (idx == 1) {
    freq = F_CPU / 8 / (times[1] - times[0]);
  }
  idx ^= 1;
}

FILE uart_file;

int main() {
  uart_init();
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  timer_init();
  sei();
  set_sleep_mode(SLEEP_MODE_IDLE);
  while (1) {
    sleep_mode();
    printf("Czestotliwosc: %u Hz\r\n", freq);
    _delay_ms(500);
  }
}
