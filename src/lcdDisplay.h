#pragma once

#ifdef MSP430
#include <Energia.h>
#else
#include <Arduino.h>
#endif

#ifndef lcdDisplay_h
#define lcdDisplay_h

class lcdDisplay
{
    // only the 4 bit interface is implemented
    private:
        uint8_t RS_pin;
        uint8_t RW_pin;
        uint8_t E_pin;
        //  [ DB7_pin, DB6_pin, DB5_pin, DB4_pin ] - 4 bit interface holds the pin indentifiers
        uint8_t pinArray[4];
        //  stores out pin states for each command  [ D7, D6, D5, D4, D3, D2, D1, D0 ]     
        uint8_t commandArray[8];   
        uint8_t LINES;              //  holds the number of display lines - can be 1 or 2 
        bool    NORMAL_FONT;        //  is true when the normal font is used
        bool    FOUR_BIT_MODE;      //  is true when using 4 bit interface (DB7,DB6,DB5, DB4)
        
        // basic instructions codes
        static const uint8_t DISPLAY_CLEAR = 0x01;
        static const uint8_t DISPLAY_HOME = 0x02;
        static const uint8_t DISPLAY_ON = 0x0C;
        static const uint8_t DISPLAY_OFF = 0x08;
        static const uint8_t SET_FUNCTION = 0x20;
        static const uint8_t SET_RAM_ADDRESS = 0x80;
        static const uint8_t SET_ENTRY_MODE = 0x04;
        
        // send basic command operation
        void sendCommand        (uint8_t command, long duration);
        // send basic data operation
        void sendData           (char data, long duration);
        // helper function that prepares the command array
        // the command array holds the state for each out pin 
        void formatCommand      (uint8_t command);
        // basic helper function for sendData and sendCommand
        void sendClock          ();
        // display a single character
        void writeCharacter     (char c);

    public:
        // main constructor
        lcdDisplay              (uint8_t rs, uint8_t rw, uint8_t e, uint8_t db7, uint8_t db6, uint8_t db5, uint8_t db4);
        ~lcdDisplay             ();
        
        // -----------------------BASIC COMMANDS-------------------------------------------

        // setup function, must be called first
        void setup              (uint8_t lines = 2, bool normal_font = true);
        // cleard the entire display and sets DDRAM addres to 0 in address counter (home)
        void displayClear       ();
        // sets DDRAM addres to 0 in address counter (start of the first line)
        void setHome            ();
        // sets the display off, cursor off and blinking off
        void displayOff         ();
        // sets interface data lenth (4 bit only), number of lines (2) and font - page 24 datasheet
        void setFunction        ();
        // sets the display off, cursor on/off or blinking on/off
        void displayOn          (bool cursor_on = false, bool blink_on = false);
        // sets cursor move direction and specifies display shift - operations during data write/read
        void setEntryMode       (bool direct = true, bool shift = false);
        // sets DDRAM adress
        void setCursorPosition  (uint8_t row, uint8_t position);

        // -----------------------AGREGATE OPERATIONS-------------------------------------------

        // write text; setCursorPosition must be called before
        void writeText          (const String &txt);

        // display an integer (negative or positive) ; setCursorPosition must be called before
        // nr_of_digits is the max number of digits (5), including leading zeros - ex: nr = 23, nr_of_digits = 4 -> 0023
        void writeNumber        (int number, const uint8_t nr_of_digits = 5);

        // display a float number (negative and positive) ; setCursorPosition must be called before
        // nr_of_digits is the max number of digits (5) for the integer part, including leading zeros - max decimals 4
        // ex: nr = 23.245, number_of_decimals = 2, nr_of_digits = 4 -> 0023.24
        void writeFloatNumber   (float number,  const uint8_t int_nr_of_digits = 3, const uint8_t nr_of_decimals = 4);

        // writes spaces 0x20 for number_of_position
        // set address must be called before
        void clearRegion        (uint8_t nr_of_positions);
};

#endif
