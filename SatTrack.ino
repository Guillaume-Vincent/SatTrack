#include <avr/pgmspace.h>
#include <LiquidCrystal.h>
#include <Satellites.h>
#include <API.h>
#include <Positions.h>
#include <StepperMotor.h>

// LCD pins
#define d4 4
#define d5 5
#define d6 6
#define d7 7
#define rs 8
#define bl 10
#define en 12

// Arduino embedded leb
#define led_pin PB5


const uint8_t t2_load = 0;
const uint8_t t2_comp = 125;

volatile bool doGotoPosition = false;
volatile bool doUpdateRequest = false;
volatile float nextAzimuth;
volatile float nextElevation;

uint16_t updateNorad;


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
PositionsList * posList = new PositionsList();


void lcdBacklightOff() {
  pinMode(bl, OUTPUT);
}

void lcdBacklightOn() {
  pinMode(bl, INPUT);
}

template <typename D>
void lcdPrintLine(int line, D data) {
  lcd.setCursor(0, line);
  lcd.print("                ");
  lcd.setCursor(0, line);
  lcd.print(data);
}

void lcdPrintSatData(int n) {
  lcdPrintLine(0, satList[n].getName());
  lcdPrintLine(1, satList[n].getNorad());
}


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

  if (++ counter == 125) {
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

  // LCD Setup
  digitalWrite(bl, LOW);
  lcd.begin(16, 2);
  lcdPrintSatData(0);

  // Stepper Setup
  pinMode(step_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);

  // Serial Setup
  Serial.begin(115200);
}

void loop() {
  static int n = 0;
  static int released = true;
  static bool switcher = true;

  int btnVal = analogRead(A0);


  if (released) {
    released = false;
    if (btnVal < 50) {
      // == Right == //
      n += 1;
      if (n >= satNumber + 1) n = 0;
      lcdPrintSatData(n);
    }
    else if (btnVal < 175) {
      // == Up == //
      lcdBacklightOn();
      lcd.display();
    }
    else if (btnVal < 290) {
      // == Down == //
      lcdBacklightOff();
      lcd.noDisplay();
    }
    else if (btnVal < 480) {
      // == Left == //
      n -= 1;
      if (n < 0) n = satNumber;
      lcdPrintSatData(n);
    }
    else if (btnVal < 800) {
      // == Select == //
      posList->clearList();
      if ((updateNorad = satList[n].getNorad()) != 0)
        getNextPositions(updateNorad, 15, posList);
    }
    else {
      // == None == //
      released = true;
    }
  }
  else if (btnVal > 1000) {
    released = true;
  }

  if (doGotoPosition) {
    doGotoPosition = false;
    Serial.print("Azimuth : ");
    Serial.print(nextAzimuth);
    Serial.print(" // Elevation : ");
    Serial.println(nextElevation);
    stepperMoveTo(nextAzimuth);
  }

  if (doUpdateRequest) {
    doUpdateRequest = false;
    getNextPositions(updateNorad, 15, posList);
  }
}
