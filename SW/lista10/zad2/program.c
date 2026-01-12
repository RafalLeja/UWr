
#include "hd44780.h"

#include <avr/io.h>

#include <stdio.h>
#include <util/delay.h>

#define COL1 0b10000
#define COL2 0b11000
#define COL3 0b11100
#define COL4 0b11110
#define COL5 0b11111

int hd44780_transmit(char data, FILE *stream) {
  LCD_WriteData(data);
  return 0;
}

int columns[] = {COL1, COL2, COL3, COL4, COL5, COL5};

void uploadColumns() {
  for (int i = 0; i < 6; i++) {
    LCD_WriteCommand(HD44780_CGRAM_SET | (i << 3));
    for (int j = 0; j < 8; j++) {
      LCD_WriteData(columns[i]);
    }
  }

  LCD_WriteCommand(HD44780_DDRAM_SET);
}

FILE hd44780_file;

int main() {
  // skonfiguruj wyświetlacz
  LCD_Initialize();
  LCD_Clear();
  uploadColumns();

  // skonfiguruj strumienie wyjściowe
  fdev_setup_stream(&hd44780_file, hd44780_transmit, NULL, _FDEV_SETUP_WRITE);
  stdout = stderr = &hd44780_file;

  LCD_GoTo(0, 0);
  int v = 0;
  while (1) {
    int i = v / 6;
    LCD_GoTo(i, 0);
    printf("%c", v % 6);
    LCD_GoTo(i, 1);
    printf("%c", v % 6);
    v++;
    if (v > 6 * 16) {
      LCD_Clear();
      v = 0;
    }
    _delay_ms(70);
  }
}
