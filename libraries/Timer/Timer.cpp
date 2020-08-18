#include "Timer.h"


void timerSetup() {
  // Reset Timer2 Control Reg A
  TCCR2A = 0;

  // Set to prescaler of 1024
  TCCR2B |= (1 << CS12);
  TCCR2B |= (1 << CS11);
  TCCR2B |= (1 << CS10);

  // Reset Timer2 and set compare value
  TCNT2 = t2_load;
  OCR2A = t2_comp;

  // Enable Timer2 compare interrupt
  TIMSK2 = (1 << OCIE2A);

  // Enable global interrupts
  sei();
}

ISR(TIMER2_COMPA_vect) {
  static int counter = 0;
  TCNT2 = t2_load;

  if (counter++ == 125) {
    counter = 0;

    if (!posList->isEmpty())
      doGotoPosition = true;
  }
}
