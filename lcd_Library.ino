#include"lcdDisplay.h"

#define MSP

#ifndef MSP
#define RS  9
#define RW  8
#define E   7
#define D7  3
#define D6  4
#define D5  5
#define D4  6
#else
#define RS  9
#define RW  8
#define E   7
#define D7  3
#define D6  4
#define D5  5
#define D4  6
#endif

lcdDisplay lcd(RS, RW, E, D7, D6, D5, D4);

void setup() {
  lcd.setup();
  lcd.displayOn();
  lcd.writeText("Voltage: ");
  lcd.setCursorPosition(2,0);
  lcd.writeText("Current: ");
  // lcd.setCursorPosition(1,9);
  // lcd.writeText("12,92");
  // lcd.setCursorPosition(2,10);
  // lcd.writeText("1,22");
  
}

void loop() {
  
}
