#include <API.h>
#include <Constants.h>
#include <Positions.h>
#include <LiquidCrystalBoard.h>
#include <ServoMotor.h>
#include <StepperMotor.h>
#include <WifiModule.h>
#include <Timer.h>


volatile bool doGotoPosition = false;
bool doUpdateRequest = false;
float nextAzimuth;
float nextElevation;
bool doMakeAPIRequest = false;
const Target * currentTargetList = NULL;


LiquidCrystalBoard lcb(rs, en, d4, d5, d6, d7);
PositionsList * posList = new PositionsList();
StepperMotor stepper;
ServoMotor servo;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;


void setup() {
  // Serial.begin(9600);
  
  lcb.init();

  timerSetup();
  wifiSetup(false);
  wifiSleep();

  servo.init();
  stepper.init();

  lcb.start();
}

void loop() {
  lcb.checkButtons();

  if (doMakeAPIRequest) {
    doMakeAPIRequest = false;
    makeAPIRequest();
  }

  if (doGotoPosition) {
    resetDoGotoPosition();

    Position * nextPos = posList->getNext();
    nextAzimuth = nextPos->getAzimuth();
    nextElevation = nextPos->getElevation();
    if (nextPos->isNextNull())
      doUpdateRequest = true;
    delete nextPos;

    lcb.lcdPrintPosData(nextAzimuth, nextElevation);

    stepper.moveTo(nextAzimuth);
    servo.moveTo(nextElevation);
  }

  if (doUpdateRequest) {
    doUpdateRequest = false;
    makeAPIRequest();
  }
}
