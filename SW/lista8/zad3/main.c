#include "FreeRTOS.h"
#include "portmacro.h"
#include "projdefs.h"
#include "queue.h"
#include "task.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

#define mainLED_TASK_PRIORITY 1
#define mainSERIAL_TASK_PRIORITY 2

#define BAUD 9600                              // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // zgodnie ze wzorem
#define BUFFER_SIZE 32                         // rozmiar buforów

xQueueHandle recvQueue;
xQueueHandle transmitQueue;
static void uart_init(void);
static int uart_transmit(char data, FILE *stream);
static int uart_receive(FILE *stream);
FILE uart_file = FDEV_SETUP_STREAM(uart_transmit, uart_receive, _FDEV_SETUP_RW);
// static void vRecieveInterruptHandler(void);
// static void vTransmitInterruptHandler(void);

static void vBlinkLed(void *pvParameters);

static void vSerial(void *pvParameters);

int main(void) {
  portENABLE_INTERRUPTS();

  xTaskHandle blink_handle;
  xTaskHandle serial_handle;

  recvQueue = xQueueCreate(BUFFER_SIZE, sizeof(char));
  transmitQueue = xQueueCreate(BUFFER_SIZE, sizeof(char));
  xTaskCreate(vBlinkLed, "blink", configMINIMAL_STACK_SIZE, NULL,
              mainLED_TASK_PRIORITY, &blink_handle);

  xTaskCreate(vSerial, "serial", configMINIMAL_STACK_SIZE, NULL,
              mainSERIAL_TASK_PRIORITY, &serial_handle);

  vTaskStartScheduler();

  return 0;
}

void vApplicationIdleHook(void) {}

/*
 * --------------------------------------------------
 */

static void uart_init(void) {
  UBRR0 = UBRR_VALUE;
  UCSR0A = 0;
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

static int uart_transmit(char data, FILE *stream) {
  // while (uxQueueSpacesAvailable(transmitQueue) == 0) {
  while (xQueueSend(transmitQueue, &data, portMAX_DELAY) == errQUEUE_FULL) {
    // bufor pełny
  }
  UCSR0B |= _BV(UDRIE0); // włącz interrupt nadawania
  return 0;
}

ISR(USART_UDRE_vect) {
  // static void vTransmitInterruptHandler(void) {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  char c;
  if (xQueueReceiveFromISR(transmitQueue, &c, &xHigherPriorityTaskWoken) ==
      pdPASS) {
    UDR0 = c;
  } else {
    UCSR0B &= ~_BV(UDRIE0);
  }

  // vPortYieldFromISR(); ??
}

static int uart_receive(FILE *stream) {
  UCSR0B |= _BV(RXCIE0);
  // while (uxQueueMessagesWaiting(recvQueue) == 0) {
  char data;
  while (xQueueReceive(recvQueue, &data, portMAX_DELAY) != pdTRUE) {
    // puste dane
  }
  return data;
}

ISR(USART_RX_vect) {
  // static void vRecieveInterruptHandler(void) {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  char c = UDR0;
  xQueueSendFromISR(recvQueue, &c, &xHigherPriorityTaskWoken);

  UCSR0B &= ~_BV(RXCIE0);

  // vPortYieldFromISR(); ??
}

/*
 * --------------------------------------------------
 */

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

  uint8_t input;

  for (;;) {
    puts("Type in the number\r\n");
    scanf("%hhu", &input);
    printf("You wrote %hhu\r\n", input);
  }
}
