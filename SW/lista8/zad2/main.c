#include "FreeRTOS.h"
#include "portmacro.h"
#include "projdefs.h"
#include "task.h"

#include <avr/io.h>

#include "queue.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>

#define mainLED_TASK_PRIORITY 2

#define mainSERIAL_TASK_PRIORITY 1

xQueueHandle queue;

static void vBlinkLed(void *pvParameters);

static void vSerial(void *pvParameters);

static int uart_receive(FILE *stream) {
  while (!(UCSR0A & _BV(RXC0)))
    taskYIELD();
  return UDR0;
}

static uint16_t getint() {
  uint16_t num = 0;
  // uint8_t len = 0;
  while (1) {
    char c = uart_receive(stdin);
    putc(c, stdout);
    if (c >= '0' && c <= '9') {
      num *= 10;
      num += c - '0';
      // len += 1;
    } else {
      // putc('\r', stdout);
      break;
    }
  }
  return num;
}

int main(void) {
  xTaskHandle blink_handle;
  xTaskHandle serial_handle;

  queue = xQueueCreate(5, sizeof(uint16_t));
  xTaskCreate(vBlinkLed, "blink", configMINIMAL_STACK_SIZE, NULL,
              mainLED_TASK_PRIORITY, &blink_handle);

  xTaskCreate(vSerial, "serial", configMINIMAL_STACK_SIZE, NULL,
              mainSERIAL_TASK_PRIORITY, &serial_handle);

  vTaskStartScheduler();

  return 0;
}

void vApplicationIdleHook(void) {}

static void vBlinkLed(void *pvParameters) {
  DDRB |= _BV(PB5);

  TickType_t waitDelay = 500;
  uint16_t t = 500;
  for (;;) {
    if (uxQueueMessagesWaiting(queue) > 0) {
      if (xQueueReceive(queue, &t, waitDelay) != pdTRUE)
        continue;
    }
    PORTB ^= _BV(PB5);
    vTaskDelay(t / portTICK_PERIOD_MS);
    PORTB ^= _BV(PB5);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

static void vSerial(void *pvParameters) {
  uart_init();
  stdin = stdout = stderr = &uart_file;

  uint16_t input;

  for (;;) {
    puts("Podaj czas\r\n");
    input = getint();
    xQueueSend(queue, &input, 1);
    // printf("%d\r\n", input);
  }
}
