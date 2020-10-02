#include <ESPWifi.h>
#include <Target.h>
#include <API.h>
#include <Positions.h>
#include <StepperMotor.h>
#include <LiquidCrystalBoard.h>
#include <Timer.h>
#include <ServoMotor.h>


volatile bool doGotoPosition = false;
volatile bool doUpdateRequest = false;
volatile float nextAzimuth;
volatile float nextElevation;
bool doMakeAPIRequest = false;
char jsonData[JSON_MAX_SIZE];
const Target * currentTargetList = NULL;

PositionsList * posList = new PositionsList();
LiquidCrystalBoard lcb(rs_pin, en_pin, A3, A2, A1, A0);
StepperMotor stepper(step_pin, dir_pin);
ServoMotor servo;
ESPWifi ESP8266(2, 3);


void setup() {
  Serial.begin(9600);
  ESP8266.begin(9600);
  
  lcb.init();
  timerSetup();

  ESP8266.init();
  servo.init();
  stepper.init();

  lcb.start();
}

void loop() {
  lcb.checkButtons();

  if (doMakeAPIRequest) {
    doMakeAPIRequest = false;
    if (ESP8266.establishConnection())
      ESP8266.makeAPIRequest(currentTargetList[lcb.getLcdPageSelected()].getID(), lcb.getSelectedMenu());
  }

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
    if (ESP8266.establishConnection())
      ESP8266.makeAPIRequest(currentTargetList[lcb.getLcdPageSelected()].getID(), lcb.getSelectedMenu());
  }
}
