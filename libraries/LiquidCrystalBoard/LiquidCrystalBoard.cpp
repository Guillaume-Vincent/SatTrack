#include "LiquidCrystalBoard.h"


// Constructor
LiquidCrystalBoard::LiquidCrystalBoard(uint8_t rs,  uint8_t enable,
	uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
: LiquidCrystal(rs, enable, d0, d1, d2, d3) {}


// Generic methods
void LiquidCrystalBoard::init() {
	digitalWrite(bl_pin, LOW);
	pinMode(stop_pin, INPUT_PULLUP);
	LiquidCrystal::begin(16, 2);
	LiquidCrystal::clear();
	
	lockButtons();
	lcdPageNb = 0;
	menuPageNb = 0;
	buttonPressed = NONE;
	selectedMenu = SETUP;

	lcdPrintWelcome();
	delay(2000);
}

void LiquidCrystalBoard::start() {
	unlockButtons();
	lcdPrintMenuData(menuPageNb);
}


// LCD related methods
void LiquidCrystalBoard::lcdBacklightOn() {
	pinMode(bl_pin, INPUT);
	LiquidCrystal::display();
}

void LiquidCrystalBoard::lcdBacklightOff() {
	LiquidCrystal::noDisplay();
	pinMode(bl_pin, OUTPUT);
}

void LiquidCrystalBoard::lcdClearLine(uint8_t line) {
	LiquidCrystal::setCursor(0, line);
	LiquidCrystal::print(LCD_VOID);
	LiquidCrystal::setCursor(0, line);
}

void LiquidCrystalBoard::lcdPrintWelcome() {
	lcdPrintLine(0, LCD_WELCOME0);
	lcdPrintLine(1, LCD_WELCOME1);
}

void LiquidCrystalBoard::lcdPrintESPTest() {
	lcdPrintLine(0, LCD_INITIALIZING);
	lcdPrintLine(1, LCD_ESP8266);
}

void LiquidCrystalBoard::lcdPrintESPFailed() {
	lcdPrintLine(1, LCD_WIFI_FAILED);
}

void LiquidCrystalBoard::lcdPrintESPSuccess() {
	lcdPrintLine(1, LCD_WIFI_SUCCESS);
}

void LiquidCrystalBoard::lcdPrintServoInit() {
	lcdPrintLine(0, LCD_INITIALIZING);
	lcdPrintLine(1, LCD_SERVO);
}

void LiquidCrystalBoard::lcdPrintServoDone() {
	lcdPrintLine(1, LCD_SERVO_DONE);
}

void LiquidCrystalBoard::lcdPrintStepperInit() {
	lcdPrintLine(0, LCD_TESTING);
	lcdPrintLine(1, LCD_STEPPER);
}

void LiquidCrystalBoard::lcdPrintStepperDone() {
	lcdPrintLine(1, LCD_STEPPER_DONE);
}

void LiquidCrystalBoard::lcdPrintMenuData(uint8_t index) {
	lcdPrintLine(0, menuList[index].getText());
	lcdClearLine(1);
}

void LiquidCrystalBoard::lcdPrintTargetData(uint8_t index) {
	long id;
	lcdPrintLine(0, currentTargetList[index].getName());
	if ((id = currentTargetList[index].getID()) != 0)
		lcdPrintLine(1, id);
}

void LiquidCrystalBoard::lcdPrintPosData(float azimuth, float elevation) {
	lcdPrintLine(0, String("A:") + String(azimuth));
    lcdPrintLine(1, String("E:") + String(elevation));
}

uint16_t LiquidCrystalBoard::getLcdPageSelected() {
	return lcdPageSelected;
}

uint16_t LiquidCrystalBoard::getMenuPageNb() {
	return menuPageNb;
}

enum LiquidCrystalBoard::menu LiquidCrystalBoard::getSelectedMenu() {
	return selectedMenu;
}


// Buttons related methods
void LiquidCrystalBoard::lockButtons() {
	buttonsLocked = true;
}

void LiquidCrystalBoard::unlockButtons() {
	buttonsLocked = false;
}

void LiquidCrystalBoard::toggleButtonsLock() {
	buttonsLocked = !buttonsLocked;
}

void LiquidCrystalBoard::checkButtons() {
	if (!buttonsLocked) {
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
}

void LiquidCrystalBoard::buttonFunction(enum button button) {
	switch (button) {
		case UP:
			if (selectedMenu != SETUP) {
				selectedMenu = SETUP;
				lcdPrintMenuData(menuPageNb);
			}
			break;

		case DOWN:
			if (selectedMenu == SETUP) {
				selectedMenu = menuList[menuPageNb].getMenu();
				currentTargetList = menuList[menuPageNb].getTargetList();
				lcdPageNb = 0;
				lcdPrintTargetData(lcdPageNb);
			}
			break;

		case RIGHT:
			if (selectedMenu == SETUP) {
				if (++menuPageNb >= MENU_COUNT)
					menuPageNb = 0;
				lcdPrintMenuData(menuPageNb);
			}
			else {
				if (++lcdPageNb >= SAT_COUNT)
					lcdPageNb = 0;
				lcdPrintTargetData(lcdPageNb);
			}
			break;

		case LEFT:
			if (selectedMenu == SETUP) {
				if (--menuPageNb >= MENU_COUNT)
					menuPageNb = MENU_COUNT - 1;
				lcdPrintTargetData(menuPageNb);
			}
			else {
				if (--lcdPageNb >= SAT_COUNT)
					lcdPageNb = SAT_COUNT - 1;
				lcdPrintTargetData(lcdPageNb);
			}
			break;

		case SELECT:
			lcdPageSelected = lcdPageNb;

			posList->clearList();
			doMakeAPIRequest = true;
			break;

		case STOP:
			posList->clearList();
			lcdPrintTargetData(lcdPageNb);
			break;

		default:
			break;
	}
}

LiquidCrystalBoard::Menu::Menu(const char* text, enum menu menuName, const Target* targetList)
: text(text), menuName(menuName), targetList(targetList) {}

const char* LiquidCrystalBoard::Menu::getText() const {
	return text;
}

enum LiquidCrystalBoard::menu LiquidCrystalBoard::Menu::getMenu() const {
	return menuName;
}

const Target* LiquidCrystalBoard::Menu::getTargetList() const {
	return targetList;
}
