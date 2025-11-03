#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <util/delay.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define IR_LED PB1

#define IR_RECV PB0
#define IR_RECV_DDR DDRB
#define IR_RECV_PORT PORTB
#define IR_RECV_PIN PINB

volatile uint8_t ir_status = 0;

void send_ir_signal() {
  TCCR1A = _BV(COM1A0);            // toggle OC1A on Compare Match
  TCCR1B = _BV(WGM12) | _BV(CS11); // CTC, Prescaler = 8
  OCR1A = 1200;
}

void stop_ir_signal() {
  TCCR1A = 0;
  TCCR1B = 0;
}

void receive_ir_signal() { ir_status = 1; }

int main(void) {

  LED_DDR |= _BV(LED) | _BV(IR_LED);
  IR_RECV_PORT |= _BV(IR_RECV); // pull-up na pinie odbiornika IR

  while (1) {
    send_ir_signal();

    for (uint8_t i = 0; i < 12 * 2; i++) {
      _delay_us(300);
      if (!(IR_RECV_PIN & _BV(IR_RECV))) {
        receive_ir_signal();
      }
    }
    stop_ir_signal();

    if (ir_status) {
      LED_PORT |= _BV(LED);
      ir_status = 0;
    } else {
      LED_PORT &= ~_BV(LED);
    }

    _delay_ms(100);
  }
}
