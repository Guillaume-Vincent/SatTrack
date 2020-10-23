#ifndef LCD_H
#define LCD_H

#include "Arduino.h"
#include "API.h"
#include "Constants.h"
#include <LiquidCrystal.h>
#include "Positions.h"
#include "Target.h"


extern PositionsList * posList;
extern bool doMakeAPIRequest;
extern const Target * currentTargetList;


const int MENU_COUNT = 3;


class LiquidCrystalBoard : public LiquidCrystal {
public:
	// Constructor
	LiquidCrystalBoard(uint8_t rs, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
	
	// Generic methods
	void init();
	void start();

	// LCD related methods
	enum menu {BODIES, SATELLITES, STARS, SETUP};
	void lcdBacklightOn();
	void lcdBacklightOff();
	void lcdClearLine(uint8_t line);
	template <class dataType> void lcdPrintLine(uint8_t line, dataType data);
	template <class dataType> void lcdPrintChar(uint8_t column, uint8_t line, dataType data);
	void lcdPrintWelcome();
	void lcdPrintWifiConnection();
	void lcdPrintWifiIP(IPAddress localIP);
	void lcdPrintWifiFailed();
	void lcdPrintServoInit();
	void lcdPrintServoDone();
	void lcdPrintStepperInit();
	void lcdPrintStepperDone();
	void lcdPrintMenuData(uint8_t index);
	void lcdPrintTargetData(uint8_t index);
	void lcdPrintPosData(float azimuth, float elevation);
	uint16_t getLcdPageSelected();
	uint16_t getMenuPageNb();
	enum menu getSelectedMenu();

	// Buttons related methods
	enum button {UP, DOWN, RIGHT, LEFT, SELECT, STOP, NONE};
	void lockButtons();
	void unlockButtons();
	void toggleButtonsLock();
	void displayButtonPressed();
	void checkButtons();
	void buttonFunction(enum button button);

	// Nested Menu Class and List
	class Menu {
	public:
		Menu(const char* text, enum menu menuName, const Target* targetList);
		const char* getText() const;
		enum menu getMenu() const;
		const Target* getTargetList() const;

	private:
		const char* text;
		enum menu menuName;
		const Target* targetList;
	};

	const LiquidCrystalBoard::Menu menuList[MENU_COUNT] = {
	LiquidCrystalBoard::Menu(BODIES_TEXT, BODIES, bodiesList),
	LiquidCrystalBoard::Menu(SATELLITES_TEXT, SATELLITES, satellitesList),
	LiquidCrystalBoard::Menu(STARS_TEXT, STARS, starsList),
	};

private:
	uint16_t lcdPageNb;
	uint16_t lcdPageSelected;
	uint16_t menuPageNb;
	enum menu selectedMenu;
	enum button buttonPressed;
	bool buttonsLocked;
};

// Template method direct implementation
template <class dataType>
void LiquidCrystalBoard::lcdPrintLine(uint8_t line, dataType data) {
	lcdClearLine(line);
	LiquidCrystal::print(data);
}

template <class dataType>
void LiquidCrystalBoard::lcdPrintChar(uint8_t column, uint8_t line, dataType data) {
	LiquidCrystal::setCursor(column, line);
	LiquidCrystal::write(data);
}



#endif
