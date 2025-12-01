/*
 * Rafał Leja 340879
 * Zadanie 3 lista 7
 */

#include "../../lib/i2c.h"
#include "../../lib/uart.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define RTC_ADDRESS 0x68
#define RTC_SECONDS 0x00
#define RTC_MINUTES 0x01
#define RTC_HOURS 0x02
#define RTC_DATE 0x04
#define RTC_MONTH 0x05
#define RTC_YEAR 0x06

uint8_t bcd_to_dec(uint8_t bcd) { return ((bcd >> 4) * 10) + (bcd & 0x0F); }
uint8_t dec_to_bcd(uint8_t dec) { return ((dec / 10) << 4) | (dec % 10); }

void print_date() {
  i2cStart();
  i2cSend((RTC_ADDRESS << 1) | 0); // adres + zapis
  i2cSend(RTC_DATE);               // ustaw rejestr na DATE
  i2cStart();
  i2cSend((RTC_ADDRESS << 1) | 1); // adres + odczyt
  uint8_t date = bcd_to_dec(i2cReadAck());
  uint8_t month = bcd_to_dec(i2cReadAck() & 0x1F);
  uint16_t year = bcd_to_dec(i2cReadNoAck()) + 2000;
  i2cStop();

  printf("Data: %02d-%02d-%04d\r\n", date, month, year);
}

void print_time() {
  i2cStart();
  i2cSend((RTC_ADDRESS << 1) | 0); // adres + zapis
  i2cSend(RTC_SECONDS);            // ustaw rejestr na SECONDS
  i2cStart();
  i2cSend((RTC_ADDRESS << 1) | 1); // adres + odczyt
  uint8_t seconds = bcd_to_dec(i2cReadAck());
  uint8_t minutes = bcd_to_dec(i2cReadAck());
  uint8_t hours = bcd_to_dec(i2cReadNoAck() & 0x2F);
  i2cStop();

  printf("Czas: %02d:%02d:%02d\r\n", hours, minutes, seconds);
}

void set_time(char *time_str, int len) {
  if (len < 8 || time_str[2] != ':' || time_str[5] != ':') {
    printf("Nieprawidlowy format czasu. Uzyj HH:MM:SS\r\n");
    return;
  }
  uint8_t hours = (time_str[0] - '0') * 10 + (time_str[1] - '0');
  uint8_t minutes = (time_str[3] - '0') * 10 + (time_str[4] - '0');
  uint8_t seconds = (time_str[6] - '0') * 10 + (time_str[7] - '0');

  i2cStart();
  i2cSend((RTC_ADDRESS << 1) | 0); // adres + zapis
  i2cSend(RTC_SECONDS);            // ustaw rejestr na SECONDS
  i2cSend(dec_to_bcd(seconds));
  i2cSend(dec_to_bcd(minutes));
  i2cSend(dec_to_bcd(hours));
  i2cStop();
}

void set_date(char *date_str, int len) {
  if (len < 10 || date_str[2] != '-' || date_str[5] != '-') {
    printf("Nieprawidlowy format daty. Uzyj DD:MM:YYYY\r\n");
    return;
  }
  uint8_t date = (date_str[0] - '0') * 10 + (date_str[1] - '0');
  uint8_t month = (date_str[3] - '0') * 10 + (date_str[4] - '0');
  uint16_t year = (date_str[6] - '0') * 1000 + (date_str[7] - '0') * 100 +
                  (date_str[8] - '0') * 10 + (date_str[9] - '0');
  if (year < 2000) {
    printf("Rok musi byc wiekszy lub rowny 2000\r\n");
    return;
  }
  i2cStart();
  i2cSend((RTC_ADDRESS << 1) | 0); // adres + zapis
  i2cSend(RTC_DATE);               // ustaw rejestr na DATE
  i2cSend(dec_to_bcd(date));
  i2cSend(dec_to_bcd(month));
  i2cSend(dec_to_bcd(year - 2000));
  i2cStop();
}

void parse_cmd(char *cmd, int len) {
  if (strncmp(cmd, "help", 4) == 0 || len < 4) {
    printf("Dostepne polecenia:\r\n");
    printf("help - wyswietl pomoc\r\n");
    printf("date - wyswietl date\r\n");
    printf("time - wyswietl czas\r\n");
    printf("set time HH:MM:SS - ustaw czas\r\n");
    printf("set date DD-MM-YYYY - ustaw date\r\n");
    printf("24h format czasu\r\n");
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
  uart_init();
  i2cInit();

  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  sei();

  printf("Witaj użytkowniku!\r\n");
  parse_cmd("help", 4);
  while (1) {
    char cmd[24] = {0};
    printf("> ");
    int len = uart_readline(&uart_file, cmd, sizeof(cmd));
    parse_cmd(cmd, len);
  }
}
