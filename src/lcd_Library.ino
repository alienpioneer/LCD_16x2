#include"lcdDisplay.h"

#define MSP430

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

unsigned short A = 5113;
float B = 123.1344;

void test(){
  delay(3000);
  lcd.setCursorPosition(1,0);
  lcd.clearRegion(16);
  lcd.setCursorPosition(1,0);
  lcd.writeText("START");
  delay(3000);
  lcd.setCursorPosition(2,0);
  lcd.clearRegion(16);
  lcd.setCursorPosition(2,0);
  lcd.writeFloatNumber((float)A/1000.00,2,2);
  delay(3000);
  lcd.setCursorPosition(1,0);
  lcd.clearRegion(16);
  lcd.setCursorPosition(1,0);
  lcd.writeNumber(5123,4);
  delay(3000);
  lcd.setCursorPosition(1,0);
  lcd.clearRegion(16);
  lcd.setCursorPosition(1,0);
  lcd.writeNumber(5123,2);
  delay(3000);
  lcd.setCursorPosition(1,0);
  lcd.clearRegion(16);
  lcd.setCursorPosition(1,0);
  lcd.writeNumber(-9876,4);
  delay(3000);
  lcd.setCursorPosition(1,0);
  lcd.clearRegion(16);
  lcd.setCursorPosition(1,0);
  lcd.writeFloatNumber(5.123,4,2);
  delay(3000);
  lcd.setCursorPosition(2,0);
  lcd.clearRegion(16);
  lcd.setCursorPosition(2,0);
  lcd.writeFloatNumber(123.12345,4,4);
  delay(3000);
  lcd.setCursorPosition(1,0);
  lcd.clearRegion(10);
  lcd.setCursorPosition(1,0);
  lcd.writeFloatNumber(12.567,2,3);
  delay(3000);
  lcd.setCursorPosition(2,0);
  lcd.clearRegion(10);
  lcd.setCursorPosition(2,0);
  lcd.writeFloatNumber(6.789,2,2);
}

void setup() {
  //Serial.begin(9600);
  lcd.setup();
  lcd.displayOn();
  lcd.writeText("Voltage: ");
  lcd.setCursorPosition(2,0);
  lcd.writeText("Current: ");
}

void loop(){
  
  test();

}
