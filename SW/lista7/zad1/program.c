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
#include <util/delay.h>

#define EEPROM_ADDRESS 0xA0

void read_addr(char *addr_str, int len) {
  uint8_t addr = 0;
  sscanf(addr_str, "%hhx", &addr);

  i2cStart();
  i2cSend(EEPROM_ADDRESS); // adres + zapis
  i2cSend(addr);           // ustaw adres do odczytu
  i2cStart();
  i2cSend(EEPROM_ADDRESS | 1); // adres + odczyt
  uint8_t data = i2cReadNoAck();
  i2cStop();

  printf("Odczytano z adresu 0x%02X: 0x%02X\r\n", addr, data);
}

void read_addr_seq(char *params, int len) {
  uint8_t addr = 0;
  uint8_t length = 0;
  sscanf(params, "%hhx %hhx", &addr, &length);

  i2cStart();
  i2cSend(EEPROM_ADDRESS); // adres + zapis
  i2cSend(addr);           // ustaw adres do odczytu
  i2cStart();
  i2cSend(EEPROM_ADDRESS | 1); // adres + odczyt

  printf("Odczytano z adresu 0x%02X: (I8HEX)\r\n", addr);
  for (uint8_t i = 0; i < length; i++) {
    uint8_t data;
    if (i < (length - 1)) {
      data = i2cReadAck();
    } else {
      data = i2cReadNoAck();
    }
    uint16_t checksum = 0x01 + (addr + i) + data;
    checksum = (~checksum + 1) & 0xFF;
    printf(":01%04X00%02X%02X\r\n", addr + i, data, checksum);
  }
  printf("\r\n");
  i2cStop();
}

void write_addr(char *params, int len) {
  uint8_t addr = 0;
  uint8_t value = 0;
  sscanf(params, "%hhx %hhx", &addr, &value);

  i2cStart();
  i2cSend(EEPROM_ADDRESS); // adres + zapis
  i2cSend(addr);           // ustaw adres do zapisu
  i2cSend(value);          // zapisz wartość
  i2cStop();

  printf("Zapisano na adres 0x%02X: 0x%02X\r\n", addr, value);
}

void write_addr_seq() {

  uint8_t count = 0;
  uint8_t offset = 0;
  while (1) {
    uint8_t byte_count = 0;
    uint16_t record_addr = 0;
    uint8_t record_type = 0;
    uint8_t buf[8] = {0};
    uint16_t checksum = 0;
    uint8_t record_checksum = 0;
    scanf(":%02hhx%04hx%02hhx", &byte_count, &record_addr, &record_type);
    if (record_type != 0) {
      printf("Koniec danych\r\n");
      // scanf("%02hhx", &record_checksum);
      break; // koniec zapisu
    }
    checksum +=
        byte_count + (record_addr >> 8) + (record_addr & 0xFF) + record_type;
    for (uint8_t j = 0; j < byte_count; j++) {
      scanf("%02hhx", &buf[j]);
      checksum += buf[j];
    }
    scanf("%02hhx", &record_checksum);
    checksum += record_checksum;
    if (checksum & 0xFF) {
      printf("Bledna suma kontrolna w rekordzie zaczynajacym sie od adresu "
             "0x%04X\r\n",
             record_addr);
      return;
    }
    if (count == 0) {
      offset = record_addr & 0xF;
      i2cStart();
      i2cSend(EEPROM_ADDRESS); // adres + zapis
      i2cSend(record_addr & 0xFF);
    }
    count += byte_count;
    for (uint8_t j = 0; j < byte_count; j++) {
      if (offset > 0xF) {
        offset = record_addr & 0xF;
        // printf("rec %x", record_addr);
        i2cStop();
        _delay_ms(10);
        i2cStart();
        i2cSend(EEPROM_ADDRESS); // adres + zapis
        i2cSend(record_addr & 0xFF);
        // return write_addr_seq();
      }
      i2cSend(buf[j]);
      record_addr++;
      offset += 1;
    }
  }
}

void parse_cmd(char *cmd, int len) {
  if (strncmp(cmd, "help", 4) == 0 || len < 4) {
    printf("Dostepne polecenia:\r\n");
    printf(" help\r\n");
    printf(" read addr\r\n");
    printf(" write addr value\r\n");
    printf(" read addr length\r\n");
    printf(" write\r\n");
  } else if (strncmp(cmd, "read", 4) == 0) {
    if (len < 6) {
      printf("Podaj adres do odczytu\r\n");
      return;
    } else if (strchr(cmd + 5, ' ') == NULL) {
      read_addr(cmd + 5, len - 5);
    } else {
      read_addr_seq(cmd + 5, len - 5);
    }
  } else if (strncmp(cmd, "write", 5) == 0) {
    if (strchr(cmd + 6, ' ') == NULL) {
      write_addr_seq();
    } else {
      write_addr(cmd + 6, len - 6);
    }
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
