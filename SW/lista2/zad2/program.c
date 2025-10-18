#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

#define DIT 300
#define BAUD 9600                              // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // zgodnie ze wzorem

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PD4
#define BTN_DDR DDRD
#define BTN_PORT PORTD
#define BTN_PIN PIND

char morse_tree[32] = {
    ' ', // [0] unused
    ' ', // [1] root
    'E', // [2] .
    'T', // [3] -
    'I', // [4] ..
    'A', // [5] .-
    'N', // [6] -.
    'M', // [7] --
    'S', // [8] ...
    'U', // [9] ..-
    'R', // [10] .-.
    'W', // [11] .--
    'D', // [12] -..
    'K', // [13] -.-
    'G', // [14] --.
    'O', // [15] ---
    'H', // [16] ....
    'V', // [17] ...-
    'F', // [18] ..-.
    ' ', // [19]
    'L', // [20] .-..
    ' ', // [21]
    'P', // [22] .--.
    'J', // [23] .---
    'B', // [24] -...
    'X', // [25] -..-
    'C', // [26] -.-.
    'Y', // [27] -.--
    'Z', // [28] --..
    'Q', // [29] --.-
    ' ', // [30]
    ' ', // [31]
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

inline void pletter(int8_t *trieIdx, int8_t *length, char *prev) {
  for (int i = 0; i < *length; i++) {
    printf("\b");
  }
  if (*trieIdx < 32 && morse_tree[*trieIdx] != ' ') {
    printf("%c", morse_tree[*trieIdx]);
    *prev = morse_tree[*trieIdx];
  } else {
    // printf("#");
  }
  *trieIdx = 1;
  *length = 0;
}

inline void finish_word() { printf(" "); }

inline void pblink() { printf("%c", (LED_PORT & _BV(LED)) == 0 ? '\\' : '/'); }

inline void pbit(int8_t bit) { printf("\033[31m%hd\033[0m", bit); }

inline void pmorse(char c) { printf("\033[96m%c\033[0m", c); }

int main(int argc, char *argv[]) {
  LED_DDR |= _BV(LED);

  BTN_PORT = _BV(BTN);

  uart_init();

  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  // char prevState = 0;
  int8_t length = 0;
  int8_t trieIdx = 1;
  char prev = 0;
  int8_t cbuf = 0;

  while (1) {
    LED_PORT ^= _BV(LED);
    _delay_ms(DIT);

    int8_t currState = BTN_PIN & _BV(BTN);
    cbuf <<= 1;
    cbuf |= (currState == 0);

    if ((cbuf & (_BV(3) - 1)) == 0b010) {
      trieIdx *= 2;
      length++;
      pmorse('.');
    } else if ((cbuf & (_BV(4) - 1)) == 0b0111) {
      trieIdx *= 2;
      trieIdx++;
      length++;
      pmorse('-');
    } else if ((cbuf & (_BV(7) - 1)) == 0 && prev != ' ') {
      // koniec słowa
      finish_word();
      prev = ' ';
    } else if ((cbuf & (_BV(3) - 1)) == 0) {
      // koniec litery
      pletter(&trieIdx, &length, &prev);
    }

    pbit(currState == 0);
    pblink();
    printf("\x1B[K\b\b");
  }

  return 0;
}
