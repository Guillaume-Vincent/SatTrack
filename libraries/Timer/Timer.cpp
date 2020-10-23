#include "Timer.h"


void timerSetup() {
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
}

void IRAM_ATTR onTimer() {
  if (!posList->isEmpty()) {
    portENTER_CRITICAL_ISR(&timerMux);
    doGotoPosition = true;
    portEXIT_CRITICAL_ISR(&timerMux);
  }
}

void resetDoGotoPosition() {
  portENTER_CRITICAL_ISR(&timerMux);
  doGotoPosition = false;
  portEXIT_CRITICAL_ISR(&timerMux);
}