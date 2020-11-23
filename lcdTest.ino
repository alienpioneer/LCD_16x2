#include"lcdDisplay.h"
// #include <LiquidCrystal.h>

//#define MSP

#ifndef MSP
#define RS  9//4
#define RW  8//5
#define E   7//6
#define D7  3//10
#define D6  4//9
#define D5  5//8
#define D4  6//7
#else
#define RS  9//4
#define RW  8//5
#define E   7//6
#define D7  3//10
#define D6  4//9
#define D5  5//8
#define D4  6//7
#endif

lcdDisplay lcd(RS, RW, E, D7, D6, D5, D4);

void setup() {
  lcd.setup();
  //lcd.displayClear();
  //lcd.setHome();
  //lcd.displayOn(true,true);
  lcd.displayOn();
  // lcd.setCursorPosition(2,4);
  // lcd.writeCharacter('A');
  // lcd.writeText("abcd");
  lcd.writeText("Voltage: ");
  lcd.setCursorPosition(2,0);
  lcd.writeText("Current: ");
  lcd.setCursorPosition(1,9);
  lcd.writeText("12,92");
  lcd.setCursorPosition(2,10);
  lcd.writeText("1,22");
  
}

void loop() {
  
}
