#include "FreeRTOS.h"
#include "portmacro.h"
#include "projdefs.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "uart.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

#define mainLED_TASK_PRIORITY 1
#define mainSERIAL_TASK_PRIORITY 2

#define STACK_SIZE configMINIMAL_STACK_SIZE + 150

// #define BAUD 9600                              // baudrate
// #define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // zgodnie ze wzorem
// #define BUFFER_SIZE 32                         // rozmiar buforów

xQueueHandle recvQueue;
xQueueHandle transmitQueue;

SemaphoreHandle_t xADCuse;
SemaphoreHandle_t xADCrunning;
SemaphoreHandle_t xUARTuse;

static void adc_init(void);
static uint16_t adc_read(uint8_t channel);
static void vPotentiometer(void *pvParameters);
static void vPhotoresistor(void *pvParameters);
static void vThermistor(void *pvParameters);

// static void uart_init(void);
// static int uart_transmit(char data, FILE *stream);
// static int uart_receive(FILE *stream);
// FILE uart_file = FDEV_SETUP_STREAM(uart_transmit, uart_receive,
// _FDEV_SETUP_RW); static void vRecieveInterruptHandler(void); static void
// vTransmitInterruptHandler(void);

int main(void) {
  portENABLE_INTERRUPTS();
  adc_init();
  uart_init();
  stdin = stdout = stderr = &uart_file;

  xTaskHandle blink_handle;
  xTaskHandle serial_handle;

  xADCuse = xSemaphoreCreateBinary();
  xADCrunning = xSemaphoreCreateBinary();
  xUARTuse = xSemaphoreCreateBinary();

  xSemaphoreGive(xADCuse);
  xSemaphoreGive(xUARTuse);
  // xSemaphoreGive(xADCrunning);

  // recvQueue = xQueueCreate(BUFFER_SIZE, sizeof(char));
  // transmitQueue = xQueueCreate(BUFFER_SIZE, sizeof(char));
  xTaskCreate(vPotentiometer, "pot", STACK_SIZE, NULL, mainSERIAL_TASK_PRIORITY,
              NULL);
  xTaskCreate(vPhotoresistor, "photo", STACK_SIZE, NULL,
              mainSERIAL_TASK_PRIORITY, NULL);
  xTaskCreate(vThermistor, "therm", STACK_SIZE, NULL, mainSERIAL_TASK_PRIORITY,
              NULL);
  // xTaskCreate(vBlinkLed, "blink", configMINIMAL_STACK_SIZE, NULL,
  //             mainLED_TASK_PRIORITY, &blink_handle);
  //
  // xTaskCreate(vSerial, "serial", configMINIMAL_STACK_SIZE, NULL,
  //             mainSERIAL_TASK_PRIORITY, &serial_handle);

  vTaskStartScheduler();

  return 0;
}

void vApplicationIdleHook(void) {}

/*
 * --------------------------------------------------
 */

static void adc_init(void) {
  ADMUX = _BV(REFS0); // referencja AVcc
  // multiplekser na 1.1V
  // ADMUX |= _BV(MUX1) | _BV(MUX2) | _BV(MUX3);
  DIDR0 =
      _BV(ADC0D) | _BV(ADC1D) | _BV(ADC2D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN) | _BV(ADIE);               // włącz ADC i interrupt
}

static uint16_t adc_read(uint8_t channel) {
  uint16_t result;
  xSemaphoreTake(xADCuse, portMAX_DELAY);
  ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

  ADCSRA |= _BV(ADSC);
  xSemaphoreTake(xADCrunning, portMAX_DELAY);

  result = ADC;
  xSemaphoreGive(xADCuse);
  return result;
}

ISR(ADC_vect) {
  // BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  xSemaphoreGiveFromISR(xADCrunning, NULL);
  // vPortYieldFromISR(); ??
}
/*
 * --------------------------------------------------
 */
//
// static void uart_init(void) {
//   UBRR0 = UBRR_VALUE;
//   UCSR0A = 0;
//   UCSR0B = _BV(RXEN0) | _BV(TXEN0);
//   UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
// }
//
// static int uart_transmit(char data, FILE *stream) {
//   // while (uxQueueSpacesAvailable(transmitQueue) == 0) {
//   while (xQueueSend(transmitQueue, &data, portMAX_DELAY) == errQUEUE_FULL) {
//     // bufor pełny
//   }
//   UCSR0B |= _BV(UDRIE0); // włącz interrupt nadawania
//   return 0;
// }
//
// ISR(USART_UDRE_vect) {
//   // static void vTransmitInterruptHandler(void) {
//   BaseType_t xHigherPriorityTaskWoken = pdFALSE;
//   char c;
//   if (xQueueReceiveFromISR(transmitQueue, &c, &xHigherPriorityTaskWoken) ==
//       pdPASS) {
//     UDR0 = c;
//   } else {
//     UCSR0B &= ~_BV(UDRIE0);
//   }
//
//   // vPortYieldFromISR(); ??
// }

// static int uart_receive(FILE *stream) {
//   UCSR0B |= _BV(RXCIE0);
//   // while (uxQueueMessagesWaiting(recvQueue) == 0) {
//   char data;
//   while (xQueueReceive(recvQueue, &data, portMAX_DELAY) != pdTRUE) {
//     // puste dane
//   }
//   return data;
// }
//
// ISR(USART_RX_vect) {
//   // static void vRecieveInterruptHandler(void) {
//   BaseType_t xHigherPriorityTaskWoken = pdFALSE;
//   char c = UDR0;
//   xQueueSendFromISR(recvQueue, &c, &xHigherPriorityTaskWoken);
//
//   UCSR0B &= ~_BV(RXCIE0);
//
//   // vPortYieldFromISR(); ??
// }

/*
 * --------------------------------------------------
 */

static void vPotentiometer(void *pvParameters) {
  uint16_t adc_value;
  for (;;) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    // adc_value = 2;
    adc_value = adc_read(2);
    xSemaphoreTake(xUARTuse, portMAX_DELAY);
    printf("P %" PRIu16 "\r\n", adc_value);
    xSemaphoreGive(xUARTuse);
  }
}
static void vPhotoresistor(void *pvParameters) {
  uint16_t adc_value;
  for (;;) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    // adc_value = 0;
    adc_value = adc_read(0);
    xSemaphoreTake(xUARTuse, portMAX_DELAY);
    printf("F %" PRIu16 "\r\n", adc_value);
    xSemaphoreGive(xUARTuse);
  }
}
static void vThermistor(void *pvParameters) {
  uint16_t adc_value;
  for (;;) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    adc_value = 1;
    // adc_value = adc_read(1);
    xSemaphoreTake(xUARTuse, portMAX_DELAY);
    printf("T %" PRIu16 "\r\n", adc_value);
    xSemaphoreGive(xUARTuse);
  }
}

// static void vBlinkLed(void *pvParameters) {
//   DDRB |= _BV(PB5);
//
//   for (;;) {
//     PORTB ^= _BV(PB5);
//     vTaskDelay(500 / portTICK_PERIOD_MS);
//   }
// }
//
// static void vSerial(void *pvParameters) {
//   uart_init();
//   stdin = stdout = stderr = &uart_file;
//
//   uint8_t input;
//
//   for (;;) {
//     puts("Type in the number\r\n");
//     scanf("%hhu", &input);
//     printf("You wrote %hhu\r\n", input);
//   }
// }
