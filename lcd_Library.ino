#include"lcdDisplay.h"
//#include <LiquidCrystal.h>

//#define MSP430

#ifdef MSP430
  #define RS  4
  #define RW  5
  #define E   6
  #define D7  10
  #define D6  9
  #define D5  8
  #define D4  7
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
//LiquidCrystal lcd(RS, RW, E, D4, D5, D6, D7);

int A = 11000;
float B = 123.1344;

void setup() {
  lcd.setup();
  lcd.displayOn();
  lcd.writeText("Voltage: ");
  lcd.setCursorPosition(2,0);
  lcd.writeText("Current: ");
  // lcd.writeText("12,92");
  // lcd.setCursorPosition(2,10);
  // lcd.writeText("1,22");
//  lcd.begin(16,2);
//  lcd.print("Voltage");
}

void loop() {
  A = A - 1;
  B = B - 0.12;
  delay(300);
  if (A>2){
      lcd.setCursorPosition(1,9);
      lcd.writeNumber(A);
      lcd.setCursorPosition(2,9);
      lcd.writeNumber(B, 3);
  };
}
