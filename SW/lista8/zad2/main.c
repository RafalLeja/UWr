#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"

#include <avr/io.h>

#include "queue.h"
#include "uart.h"
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdio.h>

#define mainLED_TASK_PRIORITY 2

#define mainSERIAL_TASK_PRIORITY 1

static void vBlinkLed(void *pvParameters);

static void vSerial(void *pvParameters);

static QueueHandle_t queue = NULL;

int main(void) {
  // Q
  queue = xQueueCreate(1, 2);

  // Create task.
  xTaskHandle blink_handle;
  xTaskHandle serial_handle;

  xTaskCreate(vBlinkLed, "blink", configMINIMAL_STACK_SIZE, NULL,
              mainLED_TASK_PRIORITY, &blink_handle);

  xTaskCreate(vSerial, "serial", configMINIMAL_STACK_SIZE, NULL,
              mainSERIAL_TASK_PRIORITY, &serial_handle);

  // Start scheduler.
  vTaskStartScheduler();

  return 0;
}

void vApplicationIdleHook(void) {}

static void vBlinkLed(void *pvParameters) {
  DDRB |= _BV(PB5);

  uint16_t time = 500;
  for (;;) {
    if (uxQueueMessagesWaiting(queue)) {
      xQueueReceive(queue, &time, 0);
    }
    PORTB |= _BV(PB5);
    vTaskDelay(time / portTICK_PERIOD_MS);
    PORTB &= ~_BV(PB5);
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

static void vSerial(void *pvParameters) {
  uart_init();
  stdin = stdout = stderr = &uart_file;

  uint16_t input;

  for (;;) {
    printf("Podaj ms: ");
    scanf("%d", &input);
    printf("Czas: %d ms\r\n", input);
    xQueueSend(queue, (void *)input, 0);
  }
}
