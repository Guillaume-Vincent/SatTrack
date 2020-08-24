#include "LiquidCrystalBoard.h"


// Constructor
LiquidCrystalBoard::LiquidCrystalBoard(uint8_t rs,  uint8_t enable,
	uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
: LiquidCrystal(rs, enable, d0, d1, d2, d3), lcdPageNb(0), buttonPressed(NONE) {}


// LCD related methods
void LiquidCrystalBoard::lcdSetup() {
	digitalWrite(bl_pin, LOW);
	pinMode(stop_pin, INPUT_PULLUP);
	LiquidCrystal::begin(16, 2);
	LiquidCrystal::clear();
	lcdPrintSatData(0);
}

void LiquidCrystalBoard::lcdBacklightOn() {
	pinMode(bl_pin, INPUT);
}

void LiquidCrystalBoard::lcdBacklightOff() {
	pinMode(bl_pin, OUTPUT);
}

void LiquidCrystalBoard::lcdClearLine(uint8_t line) {
	LiquidCrystal::setCursor(0, line);
	LiquidCrystal::print("                ");
	LiquidCrystal::setCursor(0, line);
}

void LiquidCrystalBoard::lcdPrintSatData(uint8_t satNumber) {
	lcdPrintLine(0, satList[satNumber].getName());
	lcdPrintLine(1, satList[satNumber].getNorad());
}

void LiquidCrystalBoard::lcdPrintPosData(float azimuth, float elevation) {
	lcdPrintLine(0, String("A:") + String(azimuth));
    lcdPrintLine(1, String("E:") + String(elevation));
}

uint16_t LiquidCrystalBoard::getLcdPageSelected() {
	return lcdPageSelected;
}


// Buttons related methods
void LiquidCrystalBoard::checkButtons() {
	int btnVal = analogRead(btn_pin);
	int stopVal = digitalRead(stop_pin);

	if (!stopVal and buttonPressed != STOP) {
		buttonPressed = STOP;
		buttonFunction(buttonPressed);
	}
	else if (buttonPressed == NONE) {
		if (btnVal < 50)       buttonPressed = RIGHT;
		else if (btnVal < 175) buttonPressed = UP;
		else if (btnVal < 290) buttonPressed = DOWN;
		else if (btnVal < 480) buttonPressed = LEFT;
		else if (btnVal < 800) buttonPressed = SELECT;
		buttonFunction(buttonPressed);
	}
	else if (btnVal > 1000 && stopVal) {
		buttonPressed = NONE;
	}
}

void LiquidCrystalBoard::buttonFunction(enum button button) {
	uint16_t updateNorad;

	switch (button) {
		case UP:
			lcdBacklightOn();
			LiquidCrystal::display();
			break;

		case DOWN:
			LiquidCrystal::noDisplay();
			lcdBacklightOff();
			break;

		case RIGHT:
			if (++lcdPageNb >= SAT_COUNT )
				lcdPageNb = 0;
			lcdPrintSatData(lcdPageNb);
			break;

		case LEFT:
			if (--lcdPageNb >= SAT_COUNT)
				lcdPageNb = SAT_COUNT - 1;
			lcdPrintSatData(lcdPageNb);
			break;

		case SELECT:
			lcdPageSelected = lcdPageNb;

			posList->clearList();
			if ((updateNorad = satList[lcdPageSelected].getNorad()) != 0)
				getNextPositions(updateNorad, 15, posList);
			break;

		case STOP:
			posList->clearList();
			lcdPrintSatData(lcdPageNb);
			break;

		default:
			break;
	}
}
