#include "hd44780.h"
#include "uart.h"
#include <avr/io.h>
#include <inttypes.h>
#include <stdio.h>
#include <util/delay.h>

int hd44780_transmit(char data, FILE *stream) {
  LCD_WriteData(data);
  return 0;
}

char lines[2][16] = {0};

void shiftLines() {
  LCD_GoTo(0, 0);
  for (int i = 0; i < 16; i++) {
    lines[0][i] = lines[1][i];
    printf("%c", lines[0][i]);
  }
  LCD_GoTo(0, 1);
  for (int i = 0; i < 16; i++) {
    lines[1][i] = ' ';
    printf("%c", lines[1][i]);
  }
}

FILE hd44780_file;

int main() {
  sei();
  // skonfiguruj wyświetlacz
  LCD_Initialize();
  LCD_Clear();
  LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON |
                   HD44780_CURSOR_ON | HD44780_CURSOR_BLINK);

  // skonfiguruj strumienie wyjściowe
  fdev_setup_stream(&hd44780_file, hd44780_transmit, NULL, _FDEV_SETUP_WRITE);
  stdout = stderr = &hd44780_file;

  uart_init();
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  // stdout = stderr = &uart_file;
  stdin = &uart_file;

  for (int i = 0; i < 16; i++) {
    lines[0][i] = ' ';
    lines[1][i] = ' ';
  }

  int len = 0;
  int line = 0;
  LCD_GoTo(0, 0);
  while (1) {
    char c = getchar();
    if (c == '\r' || c == '\n' || len >= 15) {
      if (len >= 15) {
        LCD_GoTo(len, line);
        lines[line][len] = c;
        printf("%c", c);
      }
      len = 0;
      if (line > 0) {
        shiftLines();
      }
      line = 1;
      LCD_GoTo(len, line);
      continue;
    }
    lines[line][len] = c;
    LCD_GoTo(len, line);
    printf("%c", c);
    len++;
  }
}
