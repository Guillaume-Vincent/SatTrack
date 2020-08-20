#include <Satellites.h>
#include <API.h>
#include <Positions.h>
#include <StepperMotor.h>
#include <LiquidCrystalBoard.h>
#include <ESPWifi.h>
#include <Timer.h>
#include <ServoMotor.h>


volatile bool doGotoPosition = false;
volatile bool doUpdateRequest = false;
volatile float nextAzimuth;
volatile float nextElevation;

PositionsList * posList = new PositionsList();
LiquidCrystalBoard lcb(rs_pin, en_pin, A0, A1, A2, A3);
StepperMotor stepper(step_pin, dir_pin);
ServoMotor servo;


void setup() {
  Serial.begin(115200);

  timerSetup();

  lcb.lcdSetup();

  servo.init(servo_pin);
}

void loop() {
  lcb.checkButtons();

  if (doGotoPosition) {
    doGotoPosition = false;

    Position * nextPos = posList->getNext();
    nextAzimuth = nextPos->getAzimuth();
    nextElevation = nextPos->getElevation();
    if (nextPos->isNextNull())
      doUpdateRequest = true;
    delete nextPos;

    Serial.print("Azimuth : ");
    Serial.print(nextAzimuth);
    Serial.print(" // Elevation : ");
    Serial.println(nextElevation);

    lcb.lcdPrintPosData(nextAzimuth, nextElevation);

    stepper.moveTo(nextAzimuth);
    servo.moveTo(nextElevation);
  }

  if (doUpdateRequest) {
    doUpdateRequest = false;
    getNextPositions(satList[lcb.getLcdPageSelected()].getNorad(), 15, posList);
  }
}
