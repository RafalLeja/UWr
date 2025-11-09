#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/sleep.h>
#include <util/delay.h>

char cbuf[31] = {0};
static uint8_t ctr = 0; // max 244

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PD4
#define BTN_DDR DDRD
#define BTN_PORT PORTD
#define BTN_PIN PIND

void io_init() {
  LED_DDR |= _BV(LED);
  BTN_PORT = _BV(BTN);
}

void timer2_init() {
  /*
   * preskaler 256
   * przerwanie co przepełnienie
   */
  TCCR2B = _BV(CS21) | _BV(CS22);
  TIMSK2 |= _BV(TOIE2);
}

ISR(TIMER2_OVF_vect) {
  ctr++;
  if (ctr >= 244) {
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
  timer2_init();

  set_sleep_mode(SLEEP_MODE_PWR_SAVE);
  sei();

  while (1) {
    sleep_mode();
  }
  return 0;
}
