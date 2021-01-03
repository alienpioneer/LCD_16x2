#pragma once

#ifdef MSP430
#include <Energia.h>
#else
#include <Arduino.h>
#endif

#ifndef lcdDisplay_h
#define lcdDisplay_h

class lcdDisplay{
    private:
        uint8_t RS_pin;
        uint8_t RW_pin;
        uint8_t E_pin;
        uint8_t pinArray[4];        //  [ DB7_pin, DB6_pin, DB5_pin, DB4_pin ];
        uint8_t commandArray[8];    //  stores pin states for each command  [ D7, D6, D5, D4, D3, D2, D1, D0 ]
        uint8_t LINES;
        uint8_t NORMAL_FONT;
        bool FOUR_BIT_MODE;
        
        static const uint8_t DISPLAY_CLEAR = 0x01;
        static const uint8_t DISPLAY_HOME = 0x02;
        static const uint8_t DISPLAY_ON = 0x0C;
        static const uint8_t DISPLAY_OFF = 0x08;
        static const uint8_t SET_FUNCTION = 0x20;
        static const uint8_t SET_RAM_ADDRESS = 0x80;
        static const uint8_t SET_ENTRY_MODE = 0x04;
        

        void formatCommand(uint8_t command);

        void sendCommand(uint8_t command, long duration);

        void sendData(char data, long duration);

        void sendClock();

    public:
        lcdDisplay(uint8_t rs, uint8_t rw, uint8_t e, uint8_t db7, uint8_t db6, uint8_t db5, uint8_t db4);

        ~lcdDisplay();

        void setup(uint8_t lines = 2, bool normal_font = true);

        void displayClear();

        void setHome();

        void displayOff();

        void setFunction();

        void displayOn(bool cursor_on = false, bool blink_on = false);

        void setEntryMode(bool direct = true, bool shift = false);

        void setCursorPosition(uint8_t row, uint8_t position);

        void writeCharacter(char c);

        void writeText(const String &txt);

        void writeNumber(int number);

        void writeNumber(float number, uint8_t decimals);
};

#endif
