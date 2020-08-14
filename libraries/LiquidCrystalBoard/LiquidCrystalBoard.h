#ifndef LCD_H
#define LCD_H

#include "Arduino.h"
#include "API.h"
#include "Positions.h"
#include "Satellites.h"
#include <LiquidCrystal.h>


extern PositionsList * posList;


const uint8_t d4 = 4;
const uint8_t d5 = 5;
const uint8_t d6 = 6;
const uint8_t d7 = 7;
const uint8_t rs = 8;
const uint8_t bl = 10;
const uint8_t en = 12;
const uint8_t btn_pin = A5;



class LiquidCrystalBoard : public LiquidCrystal{
public:
	// Constructor
	LiquidCrystalBoard(uint8_t rs, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
	
	// LCD related methods
	void lcdSetup();
	void lcdBacklightOn();
	void lcdBacklightOff();
	void lcdClearLine(uint8_t line);
	template <class dataType> void lcdPrintLine(uint8_t line, dataType data);
	void lcdPrintSatData(uint8_t satNumber);
	uint16_t getLcdPageSelected();

	// Buttons related methods
	enum button {UP, DOWN, RIGHT, LEFT, SELECT, NONE};
	void checkButtons();
	void buttonFunction(enum button button);

private:
	uint16_t lcdPageNb;
	uint16_t lcdPageSelected;
	enum button buttonPressed;
};

// Template method direct implementation
template <class dataType>
void LiquidCrystalBoard::lcdPrintLine(uint8_t line, dataType data) {
	lcdClearLine(line);
	LiquidCrystal::print(data);
}


#endif
