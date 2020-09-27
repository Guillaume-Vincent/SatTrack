#include <ESPWifi.h>
#include <Satellites.h>
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
char jsonData[JSON_MAX_SIZE];

PositionsList * posList = new PositionsList();
LiquidCrystalBoard lcb(rs_pin, en_pin, A3, A2, A1, A0);
StepperMotor stepper(step_pin, dir_pin);
ServoMotor servo;

ESPWifi ESP8266(2, 3);


void setup() {
  Serial.begin(9600);
  ESP8266.begin(9600);
  
  timerSetup();

  // lcb.lcdSetup();

  ESP8266.init();

  // servo.init(servo_pin);

  // stepper.test();
}

void loop() {
  unsigned long t0 = millis();
  if (ESP8266.establishConnection()) {
    ESP8266.makeAPIRequest(25544);
    Serial.println(millis() - t0);
  }
  Serial.println("Done");
  /*
  
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
  */
}
