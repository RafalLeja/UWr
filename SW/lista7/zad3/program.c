#include "../../lib/uart.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <string.h>

void print_date() {}

void print_time() {}

void set_time(char *time_str, int len) {}

void set_date(char *date_str, int len) {}

void parse_cmd(char *cmd, int len) {
  if (strncmp(cmd, "help", 4) == 0 || len < 4) {
    printf("Dostepne polecenia:\r\n");
    printf("help - wyswietl pomoc\r\n");
    printf("date - wyswietl date\r\n");
    printf("time - wyswietl czas\r\n");
    printf("set time HH:MM:SS - ustaw czas\r\n");
    printf("set date DD:MM:YYYY - ustaw date\r\n");
  } else if (strncmp(cmd, "date", 4) == 0) {
    print_date();
  } else if (strncmp(cmd, "time", 4) == 0) {
    print_time();
  } else if (strncmp(cmd, "set time", 8) == 0) {
    set_time(cmd + 9, len - 9);
  } else if (strncmp(cmd, "set date", 8) == 0) {
    set_date(cmd + 9, len - 9);
  } else {
    printf("Nieznane polecenie\r\n");
  }
}

int main() {
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  sei(); // włącz globalne przerwania
  // program testowy
  printf("Hello world!\r\n");
  while (1) {
    char cmd[20] = {0};
    int len = uart_readline(&uart_file, cmd, sizeof(cmd));
    parse_cmd(cmd, len);
    printf("Odczytano: %s\r\n", cmd);
  }
}
