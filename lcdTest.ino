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

void writeAB(){
  pinMode(RS, OUTPUT);
  pinMode(RW, OUTPUT);
  pinMode(E, OUTPUT);
  digitalWrite(RS, LOW);
  digitalWrite(RW, LOW);
  digitalWrite(E, LOW);
  pinMode(D7, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D4, OUTPUT);
  digitalWrite(D7, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D4, LOW);

  delayMicroseconds(60000);

  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 1);
  digitalWrite(D4, 1);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(5000);

  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 1);
  digitalWrite(D4, 1);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(5000);

  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 1);
  digitalWrite(D4, 1);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(150);

  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 1);
  digitalWrite(D4, 0);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(50);

  // set func 4 bit 2 lines
  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 1);
  digitalWrite(D4, 0);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(50);
  digitalWrite(D7, 1);
  digitalWrite(D6, 0);
  digitalWrite(D5, 0);
  digitalWrite(D4, 0);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(50);

  // display off
  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 0);
  digitalWrite(D4, 0);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(50);
  digitalWrite(D7, 1);
  digitalWrite(D6, 0);
  digitalWrite(D5, 0);
  digitalWrite(D4, 0);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(50);

  // display clear
  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 0);
  digitalWrite(D4, 0);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(50);
  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 0);
  digitalWrite(D4, 1);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(3000);

  // entry mode
  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 0);
  digitalWrite(D4, 0);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(50);
  digitalWrite(D7, 0);
  digitalWrite(D6, 1);
  digitalWrite(D5, 1);
  digitalWrite(D4, 0);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(50);

  // display on
  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 0);
  digitalWrite(D4, 0);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(50);
  digitalWrite(D7, 1);
  digitalWrite(D6, 1);
  digitalWrite(D5, 1);
  digitalWrite(D4, 1);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(50);

  // 'A'
  digitalWrite(RS, 1);
  digitalWrite(D7, 0);
  digitalWrite(D6, 1);
  digitalWrite(D5, 0);
  digitalWrite(D4, 0);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(50);
  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 0);
  digitalWrite(D4, 1);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(50);
  digitalWrite(RS,0);

  // 'B'
  digitalWrite(RS, 1);
  digitalWrite(D7, 0);
  digitalWrite(D6, 1);
  digitalWrite(D5, 0);
  digitalWrite(D4, 0);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(50);
  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 1);
  digitalWrite(D4, 0);
  digitalWrite(E, 0);
  delayMicroseconds(10);
  digitalWrite(E, 1);
  delayMicroseconds(10);
  digitalWrite(E, 0);
  delayMicroseconds(50);
  digitalWrite(RS,0);
}

// LiquidCrystal lcd(RS, RW, E, D4, D5, D6, D7);
lcdDisplay lcd(RS, RW, E, D7, D6, D5, D4);

void setup() {
  lcd.setup();
  // // // //lcd.displayClear();
  // // // //lcd.setHome();
  
  lcd.displayOn(true,true);
  lcd.setCursorPosition(2,4);
  // lcd.writeCharacter('A');
  lcd.writeText("abcd");
  // lcd.begin(16, 2);
  // lcd.print("Voltage: ");
  // lcd.setCursor(0,2);
  // lcd.print("Current: ");
  // lcd.setCursor(9,0);
  // lcd.print("12,92");
  // lcd.setCursor(10,2);
  // lcd.print("1,22");
  // writeAB();
  
}

void loop() {
  
  //lcd.sendClock();
  
}
