#include "lcdDisplay.h"

lcdDisplay::lcdDisplay(uint8_t rs, uint8_t rw, uint8_t e, uint8_t db7, uint8_t db6, uint8_t db5, uint8_t db4){
    RS_pin = rs; RW_pin = rw; E_pin = e;
    pinArray[0] = db7;
    pinArray[1] = db6;
    pinArray[2] = db5;
    pinArray[3] = db4;
    FOUR_BIT_MODE = true;
    pinMode(RS_pin, OUTPUT);
    pinMode(RW_pin, OUTPUT);
    pinMode(E_pin, OUTPUT);
    for(uint8_t i=0; i<4; i++)
        pinMode(pinArray[i], OUTPUT);
}

void lcdDisplay::setup(uint8_t lines, bool normal_font){
    LINES  = lines;
    NORMAL_FONT = normal_font;

    delayMicroseconds(60000);
    digitalWrite(RS_pin, LOW);
    digitalWrite(RW_pin, LOW);
    digitalWrite(E_pin, LOW);


    // Force init
    

    if (FOUR_BIT_MODE){
        formatCommand(0x30);
        for (uint8_t i=0; i<=3; i++){
            digitalWrite(pinArray[i], commandArray[i]);
        };
        sendClock();
        delayMicroseconds(5000);

        sendClock();
        delayMicroseconds(5000);

        sendClock();
        delayMicroseconds(150);

        formatCommand(0x20);
        for (uint8_t i=0; i<=3; i++){
            digitalWrite(pinArray[i], commandArray[i]);
        };
        sendClock();

        setFunction();

        displayOff();

        displayClear();

        setEntryMode();
    }
}

void lcdDisplay::sendClock(){
    digitalWrite(E_pin, LOW);
    delayMicroseconds(10); 
    digitalWrite(E_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(E_pin, LOW);
    delayMicroseconds(50);
}

void lcdDisplay::formatCommand(uint8_t command){
    uint8_t mask = 0x80;
    uint8_t tmp;
    for (uint8_t i=0;i<8;i++){
        tmp = command & mask;
        if (tmp != 0) tmp = 1;
        commandArray[i] = tmp;
        mask = mask >> 1;
    };
}

void lcdDisplay::sendData(char data, long duration){
    formatCommand(data);
    digitalWrite(RS_pin, HIGH);
    digitalWrite(RW_pin, LOW);
    for (uint8_t i=0; i<=7; i++){
        digitalWrite(pinArray[i%4], commandArray[i]);
        if (i==3 || i==7)
            sendClock();
    };
    delayMicroseconds(duration);
}

void lcdDisplay::sendCommand(uint8_t command, long duration){
    // pinArray [ DB7_pin, DB6_pin, DB5_pin, DB4_pin ];
    // commandArray  [ D7, D6, D5, D4, D3, D2, D1, D0 ]
    formatCommand(command);
    digitalWrite(RS_pin, LOW);
    digitalWrite(RW_pin, LOW);
    for (uint8_t i=0; i<=7; i++){
        digitalWrite(pinArray[i%4], commandArray[i]);
        if (i==3 || i==7)
            sendClock();
    };
    delayMicroseconds(duration);
}

void lcdDisplay::setFunction(){
    uint8_t command = SET_FUNCTION;
    if (FOUR_BIT_MODE == false)
        command += 0x10;                    // Data length 8 bits - 0001 0000
    if (LINES == 2)
        command += 0x08;                    // - 0000 1000
    if (NORMAL_FONT == false)
        command += 0x04;                    // - 0000 0100 
    lcdDisplay::sendCommand((uint8_t)command, 40);   // 70 us
}

void lcdDisplay::setCursorPosition(uint8_t row, uint8_t position){
    uint8_t command = SET_RAM_ADDRESS;
    if (row == 1)
        command += position;
    else{
        command += 0x40;
        command += position;
    }
    lcdDisplay::sendCommand((uint8_t)command, 40);
}

void lcdDisplay::writeCharacter(const char c){
    lcdDisplay::sendData(c, 50);
}

void lcdDisplay::writeText(const String &txt){
    for(uint16_t i=0; i<txt.length(); i++){
        writeCharacter(txt[i]);
        delayMicroseconds(40);
    }   
 }

void lcdDisplay::displayOff(){
    lcdDisplay::sendCommand(DISPLAY_OFF, 60);
    delayMicroseconds(2000);
}

void lcdDisplay::displayClear(){
    lcdDisplay::sendCommand(DISPLAY_CLEAR, 60);
    delayMicroseconds(4000);
}

void lcdDisplay::displayOn(bool cursor_on, bool blink_on){
    uint8_t command = DISPLAY_ON;
    if (cursor_on)
        command += 0x02;
    if (blink_on)
        command += 0x01;
    lcdDisplay::sendCommand(command, 50);
}

void lcdDisplay::setEntryMode(bool direct, bool shift){
    uint8_t command = SET_ENTRY_MODE;
    if (direct)
        command +=0x02;
    if (shift)
        command +=0x01;
    lcdDisplay::sendCommand(SET_ENTRY_MODE, 50);
}

void lcdDisplay::setHome(){
    lcdDisplay::sendCommand(DISPLAY_HOME, 40);
    delayMicroseconds(50000);
}

lcdDisplay::~lcdDisplay(){};