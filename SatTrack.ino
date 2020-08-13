#include <Satellites.h>
#include <API.h>
#include <Positions.h>
#include <StepperMotor.h>
#include <LiquidCrystalBoard.h>


// Arduino embedded leb
#define led_pin PB5


const uint8_t t2_load = 0;
const uint8_t t2_comp = 125;

volatile bool doGotoPosition = false;
volatile bool doUpdateRequest = false;
volatile float nextAzimuth;
volatile float nextElevation;

uint16_t updateNorad;

PositionsList * posList = new PositionsList();
LiquidCrystalBoard lcb(rs, en, d4, d5, d6, d7);


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
    if (!posList->isEmpty()) {
      doGotoPosition = true;

      Position * nextPos = posList->getNext();
      nextAzimuth = nextPos->getAzimuth();
      nextElevation = nextPos->getElevation();

      if (nextPos->isNextNull())
        doUpdateRequest = true;

      delete nextPos;
    }

    PORTB ^= (1 << led_pin);
    counter = 0;
  }
}


void setup() {
  // Timer Setup
  DDRB |= (1 << led_pin);
  timerSetup();

  // LCB Setup
  lcb.lcdSetup();

  // Stepper Setup
  stepperSetup();

  // Serial Setup
  Serial.begin(115200);
}

void loop() {
  lcb.checkButtons();

  if (doGotoPosition) {
    doGotoPosition = false;
    Serial.print("Azimuth : ");
    Serial.print(nextAzimuth);
    Serial.print(" // Elevation : ");
    Serial.println(nextElevation);
    // stepperMoveTo(nextAzimuth);
  }

  if (doUpdateRequest) {
    doUpdateRequest = false;
    getNextPositions(satList[lcb.getLcdPageSelected()].getNorad(), 15, posList);
  }
}
