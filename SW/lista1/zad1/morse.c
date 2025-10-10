#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB
#define DIT 500
#define BAUD 9600                              // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // zgodnie ze wzorem

char morse[] = {
    0b00010010, 0b11100100, 0b10100100, 0b01100011, 0b00010001, 0b10110100,
    0b01000011, 0b11110100, 0b00110010, 0b00010100, 0b00100011, 0b11010100,
    0b00000010, 0b00100010, 0b00000011, 0b10010100, 0b01000100, 0b01010011,
    0b01110011, 0b00000001, 0b00110011, 0b01110100, 0b00010011, 0b01100100,
    0b00100100, 0b11000100,
};

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

void sendMorseLetter(char letter) {
  if (letter < 97 || letter > 122) {
    printf("Niewspierany znak\n");
    return;
  }

  int code = letter - 97;
  int length = morse[code] & 0xF;
  int bits = (morse[code] & 0xF0) >> 4;
  for (int i = 0; i < length; i++) {
    if (bits & 0b1) {
      // krotkie
      LED_PORT |= _BV(LED);
      _delay_ms(DIT);
      LED_PORT &= ~_BV(LED);
    } else {
      // dlugie
      LED_PORT |= _BV(LED);
      _delay_ms(3 * DIT);
      LED_PORT &= ~_BV(LED);
    }

    // przerwa
    _delay_ms(DIT);
    bits = bits >> 1;
  }
}

int main() {
  LED_DDR |= _BV(LED);
  uart_init();

  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  while (1) {
    char letter = 0;
    scanf("%c", &letter);
    sendMorseLetter(letter);

    // LED_PORT |= _BV(LED);
    // _delay_ms(1000);
    // LED_PORT &= ~_BV(LED);
    // _delay_ms(1000);
  }
}
