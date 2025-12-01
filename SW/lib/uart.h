#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>

#define BAUD 9600                              // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // zgodnie ze wzorem
#define BUFFER_SIZE 32                         // rozmiar buforów
#define ECHO 1

extern char t_buf[BUFFER_SIZE];
extern char r_buf[BUFFER_SIZE];
extern uint8_t t_head;
extern uint8_t t_tail;
extern volatile uint8_t r_head;
extern volatile uint8_t r_tail;
extern FILE uart_file;

void uart_init();
int uart_transmit(char data, FILE *stream);
int uart_receive(FILE *stream);
char uart_readline(FILE *stream, char *buf, uint8_t maxlen);

ISR(USART_UDRE_vect);
ISR(USART_RX_vect);
