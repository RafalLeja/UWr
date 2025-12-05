#include "FreeRTOS.h"
#include "task.h"

#include <avr/io.h>

#include "uart.h"
#include <stdio.h>

#define mainLED_TASK_PRIORITY 2

#define mainSERIAL_TASK_PRIORITY 1

static void vBlinkLed(void *pvParameters);

static void vSerial(void *pvParameters);

int main(void) {
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

  for (;;) {
    PORTB ^= _BV(PB5);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

static void vSerial(void *pvParameters) {
  uart_init();
  stdin = stdout = stderr = &uart_file;

  char input;

  for (;;) {
    puts("Hello World\r\n");
    input = getchar();
    printf("You wrote %c\r\n", input);
  }
}
