/*
 * Rafał Leja
 * lista 6 zadanie 1 "echo"
 */
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>

#define BAUD 9600
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1)

void uart_init(void) {
  // baud rate
  UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
  UBRR0L = (uint8_t)(UBRR_VALUE & 0xFF);
  // Enable receiver and transmitter
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  // Recieve interrupt enable
  UCSR0B |= (1 << RXCIE0);
  // Set frame format: 8 data bits, 1 stop bit
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

ISR(USART_RX_vect) {
  uint8_t data = UDR0;

  while (!(UCSR0A & (1 << UDRE0)))
    ;
  UDR0 = data;
}

int main(void) {
  uart_init();
  sei();
  set_sleep_mode(SLEEP_MODE_IDLE);
  while (1) {
    sleep_mode();
  }
}
