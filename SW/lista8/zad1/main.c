#include "FreeRTOS.h"
#include "task.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define mainBTN_TASK_PRIORITY 1
#define mainKITT_TASK_PRIORITY 1

#define KITT_LED_DDR DDRD
#define KITT_LED_PORT PORTD

#define WIDTH 5
#define TIME 50

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB1
#define BTN_DDR DDRB
#define BTN_PORT PORTB
#define BTN_PIN PINB

char cbuf[100] = {0};

static void vButtonDelay(void *pvParameters) {
  LED_DDR |= _BV(LED);

  BTN_PORT = _BV(BTN);

  int ctr = 0;
  while (1) {
    LED_PORT |= cbuf[ctr];

    if (BTN_PIN & _BV(BTN)) {
      cbuf[ctr] |= _BV(LED);
    } else {
      cbuf[ctr] &= ~_BV(LED);
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);
    LED_PORT &= ~_BV(LED);
    ctr++;
    if (ctr >= 100) {
      ctr %= 100;
    }
  }
}

static void nextFrame(uint8_t *curr, uint8_t *direction) {
  if (*curr >= 0x80 || *curr <= 1) {
    *direction = 1 - *direction;
  }
  if (*direction) {
    *curr = *curr >> 1;
  } else {
    *curr = *curr << 1;
  }
}

static void vKitt(void *pvParameters) {
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  KITT_LED_DDR |= 0xFF;
  uint8_t curr = 64, direction = 0;
  while (1) {
    nextFrame(&curr, &direction);

    KITT_LED_PORT =
        (curr << 2) | (curr << 1) | curr | (curr >> 1) | (curr >> 2);
    vTaskDelay(TIME / portTICK_PERIOD_MS);
  }
}

int main(void) {
  // Create task.
  xTaskHandle blink_handle;
  xTaskHandle serial_handle;

  xTaskCreate(vKitt, "kitt", configMINIMAL_STACK_SIZE, NULL,
              mainKITT_TASK_PRIORITY, &blink_handle);

  xTaskCreate(vButtonDelay, "serial", configMINIMAL_STACK_SIZE, NULL,
              mainBTN_TASK_PRIORITY, &serial_handle);

  // Start scheduler.
  vTaskStartScheduler();

  return 0;
}

void vApplicationIdleHook(void) {}
