#include "LiquidCrystalBoard.h"


// Constructor
LiquidCrystalBoard::LiquidCrystalBoard(uint8_t rs,  uint8_t enable,
	uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
: LiquidCrystal(rs, enable, d4, d5, d6, d7) {}


// Generic methods
void LiquidCrystalBoard::init() {
	digitalWrite(bl, LOW);
	LiquidCrystal::begin(16, 2);
	LiquidCrystal::clear();
	
	lockButtons();
	lcdPageNb = 0;
	menuPageNb = 0;
	buttonPressed = NONE;
	selectedMenu = SETUP;

	countUp = 0;
	countDown = 0;
	countLeft = 0;
	countRight = 0;
	countSelect = 0;

	lcdPrintWelcome();
	delay(2000);
}

void LiquidCrystalBoard::start() {
	unlockButtons();
	lcdPrintMenuData(menuPageNb);
}


// LCD related methods
void LiquidCrystalBoard::lcdBacklightOn() {
	pinMode(bl, INPUT);
	LiquidCrystal::display();
}

void LiquidCrystalBoard::lcdBacklightOff() {
	LiquidCrystal::noDisplay();
	pinMode(bl, OUTPUT);
}

void LiquidCrystalBoard::lcdClearLine(uint8_t line) {
	LiquidCrystal::setCursor(0, line);
	LiquidCrystal::print(LCD_VOID);
	LiquidCrystal::setCursor(0, line);
}

void LiquidCrystalBoard::resetLcd() {
	buttonFunction(STOP);
	unlockButtons();
}

void LiquidCrystalBoard::lcdPrintWelcome() {
	lcdPrintLine(0, LCD_WELCOME0);
	lcdPrintLine(1, LCD_WELCOME1);
}

void LiquidCrystalBoard::lcdPrintWifiConnection() {
	lcdPrintLine(0, LCD_INITIALIZING);
	lcdPrintLine(1, LCD_WIFI32);
}

void LiquidCrystalBoard::lcdPrintWifiIP(IPAddress localIP) {
	lcdPrintLine(0, LCD_WIFICONNECT);
	lcdClearLine(1);
	LiquidCrystal::setCursor(1, 1);
	LiquidCrystal::print(localIP);
}

void LiquidCrystalBoard::lcdPrintWifiFailed() {
	lcdPrintLine(0, LCD_WIFI_FAILED);
	lcdPrintLine(1, LCD_WIFIRETRY);
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

void LiquidCrystalBoard::lcdPrintStepperTest() {
	lcdPrintLine(0, LCD_STEPPER_TEST);
	lcdClearLine(1);
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
	else
		lcdClearLine(1);
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
void LiquidCrystalBoard::countAdd(enum button button) {
	countUp = (countUp + 1) * (button == UP);
	countDown = (countDown + 1) * (button == DOWN);
	countLeft = (countLeft + 1) * (button == LEFT);
	countStop = (countStop + 1) * (button == STOP); 
	countRight = (countRight + 1) * (button == RIGHT);
	countSelect = (countSelect + 1) * (button == SELECT);
}

void LiquidCrystalBoard::lockButtons() {
	buttonsLocked = true;
}

void LiquidCrystalBoard::unlockButtons() {
	buttonsLocked = false;
}

void LiquidCrystalBoard::toggleButtonsLock() {
	buttonsLocked = !buttonsLocked;
}

void LiquidCrystalBoard::displayButtonPressed() {
	switch (buttonPressed) {
		// case NONE:
		//  	Serial.println("NONE");
		//  	break;
		case RIGHT:
			Serial.println("RIGHT");
			break;
		case UP:
			Serial.println("UP");
			break;
		case DOWN:
			Serial.println("DOWN");
			break;
		case LEFT:
			Serial.println("LEFT");
			break;
		case SELECT:
			Serial.println("SELECT");
			break;
		case STOP:
			Serial.println("STOP");
			break;
		default:
			break;
	}
}

void LiquidCrystalBoard::checkButtons() {
	int btnVal = analogRead(btn);

	if (buttonPressed == NONE) {
		if (btnVal < 341) {
			if (countSelect >= DEBOUNCE_COUNTER) {
				buttonPressed = SELECT;
				countAdd(NONE);
			}
			else countAdd(SELECT);
		}
		else if (btnVal < 1024) {
			if (countLeft >= DEBOUNCE_COUNTER) {
				buttonPressed = LEFT;
				countAdd(NONE);
			}
			else countAdd(LEFT);
		}
		else if (btnVal < 1706) {
			if (countUp >= DEBOUNCE_COUNTER) {
				buttonPressed = UP;
				countAdd(NONE);
			}
			else countAdd(UP);
		}
		else if (btnVal < 2389) {
			if (countDown >= DEBOUNCE_COUNTER) {
				buttonPressed = DOWN;
				countAdd(NONE);
			}
			else countAdd(DOWN);
		}
		else if (btnVal < 3071) {
			if (countRight >= DEBOUNCE_COUNTER) {
				buttonPressed = RIGHT;
				countAdd(NONE);
			}
			else countAdd(RIGHT);
		}
		else if (btnVal < 3754) {
			if (countStop >= DEBOUNCE_COUNTER) {
				buttonPressed = STOP;
				countAdd(NONE);
			}
			else countAdd(STOP);
		}
		
		if (!buttonsLocked || buttonPressed == STOP) {
			// displayButtonPressed();
			buttonFunction(buttonPressed);
		}
	}
	else if (btnVal >= 3754) {
		buttonPressed = NONE;
	}
}

void LiquidCrystalBoard::buttonFunction(enum button button) {
	int counter = 0;
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
				if (selectedMenu == BODIES) counter = BODY_COUNT;
				else if (selectedMenu == SATELLITES) counter = SAT_COUNT;
				else if (selectedMenu == STARS) counter = STAR_COUNT;

				if (++lcdPageNb >= counter)
					lcdPageNb = 0;
				lcdPrintTargetData(lcdPageNb);
			}
			break;

		case LEFT:
			if (selectedMenu == SETUP) {
				if (--menuPageNb >= MENU_COUNT)
					menuPageNb = MENU_COUNT - 1;
				lcdPrintMenuData(menuPageNb);
			}
			else {
				if (selectedMenu == BODIES) counter = BODY_COUNT;
				else if (selectedMenu == SATELLITES) counter = SAT_COUNT;
				else if (selectedMenu == STARS) counter = STAR_COUNT;
				
				if (--lcdPageNb >= counter)
					lcdPageNb = counter - 1;
				lcdPrintTargetData(lcdPageNb);
			}
			break;

		case SELECT:
			if (selectedMenu == SETUP) {
				selectedMenu = menuList[menuPageNb].getMenu();
				currentTargetList = menuList[menuPageNb].getTargetList();
				lcdPageNb = 0;
				lcdPrintTargetData(lcdPageNb);
			}
			else {
				lockButtons();
				lcdPageSelected = lcdPageNb;

				posList->clearList();
				doMakeAPIRequest = true;
			}
			break;

		case STOP:
			unlockButtons();
			if (selectedMenu != SETUP) {
				posList->clearList();
				lcdPrintTargetData(lcdPageNb);
			}
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
