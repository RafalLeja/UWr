#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <avr/sleep.h>
#include <util/delay.h>
#define STEPS 61

char cbuf[(STEPS + 7) / 8] = {0};
static uint8_t ctr = 0; // max 244

#define LED PB2
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PA7
#define BTN_DDR DDRA
#define BTN_PORT PORTA
#define BTN_PIN PINA

void io_init() {
  LED_DDR |= _BV(LED);
  BTN_PORT = _BV(BTN);
}

void timer0_init() {
  /*
   * preskaler 256
   * przerwanie co przepełnienie
   */
  TCCR0B = _BV(CS01) | _BV(CS00);
  TIMSK0 |= _BV(TOIE0);
}

ISR(TIM0_OVF_vect) {
  // // LED_PORT ^= _BV(LED);
  // if (BTN_PIN & _BV(BTN)) {
  //   LED_PORT |= _BV(LED);
  // } else {
  //   LED_PORT &= ~_BV(LED);
  // }
  ctr++;
  if (ctr >= STEPS) {
    ctr = 0;
  }

  uint8_t index = ctr / 8;
  uint8_t bit = ctr % 8;
  if ((cbuf[index] & (1 << bit)) > 0) {
    LED_PORT |= _BV(LED);
  } else {
    LED_PORT &= ~_BV(LED);
  }

  if (BTN_PIN & _BV(BTN)) {
    cbuf[index] &= ~(1 << bit);
  } else {
    cbuf[index] |= (1 << bit);
  }
}

int main(int argc, char *argv[]) {
  io_init();
  timer0_init();
  sei();

  set_sleep_mode(SLEEP_MODE_IDLE);
  sei();

  while (1) {
    sleep_mode();
  }

  return 0;
}
