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
        delayMicroseconds(4500);

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
    if (FOUR_BIT_MODE == false){
        // Data length 8 bits - 0001 0000
        command += 0x10;
    }
    if (LINES == 2){
        // - 0000 1000
        command += 0x08;
    }                     
    if (NORMAL_FONT == false){
        // - 0000 0100
        command += 0x04;
    }                    
    sendCommand((uint8_t)command, 40);   // 70 us
}


void lcdDisplay::setCursorPosition(uint8_t row, uint8_t position){
    uint8_t command = SET_RAM_ADDRESS;
    if (row == 1)
        command += position;
    else{
        command += 0x40;
        command += position;
    }
    sendCommand((uint8_t)command, 40);
}


void lcdDisplay::writeCharacter(char c){
    sendData(c, 50);
}


void lcdDisplay::writeText(const String &txt){
    for(uint16_t i=0; i<txt.length(); i++){
        writeCharacter(txt[i]);
        delayMicroseconds(40);
    }   
}


void lcdDisplay::displayOff(){
    sendCommand(DISPLAY_OFF, 60);
    delayMicroseconds(2000);
}


void lcdDisplay::displayClear(){
    sendCommand(DISPLAY_CLEAR, 60);
    delayMicroseconds(4000);
}


void lcdDisplay::displayOn(bool cursor_on, bool blink_on){
    uint8_t command = DISPLAY_ON;
    if (cursor_on)
        command += 0x02;
    if (blink_on)
        command += 0x01;
    sendCommand(command, 50);
}


void lcdDisplay::setEntryMode(bool direct, bool shift){
    uint8_t command = SET_ENTRY_MODE;
    if (direct == true)
        command +=0x02;
    if (shift == true)
        command +=0x01;
    sendCommand(command, 50);
}


void lcdDisplay::setHome(){
    sendCommand(DISPLAY_HOME, 40);
    delayMicroseconds(50000);
}


void lcdDisplay::writeNumber(int number, const uint8_t nr_of_digits){
    // setCursorPosition must be called before
    // maximum 5 digits
    // nr_of_digits is the max number of digits, including leading zeros
    // ex: nr = 23, nr_of_digits = 4 -> 0023

    bool is_negative = false;
    uint8_t digits[nr_of_digits];
	uint8_t i = 0;

    if (number < 0){
        is_negative = true;
        number *=-1;
    };
    while(i <= nr_of_digits - 1){
        // ascii ofset for 0 is 48
        digits[i] = static_cast<uint8_t>(number % 10)+48;
        number = number / 10;
        i++;
    };
    if (is_negative){
        writeCharacter('-');
    };
    while(i>0){
    	i--;
    	writeCharacter(digits[i]);
    };
}


void lcdDisplay::writeFloatNumber(float number,  const uint8_t int_nr_of_digits, const uint8_t nr_of_decimals){
    // setCursorPosition must be called before
    // MAX 4 decimals
    // nr_of_digits is the max number of digits, including leading zeros
    // ex: nr = 23.245, number_of_decimals = 2, nr_of_digits = 4 -> 0023.24

    const uint16_t dec_mult[4] = {10, 100, 1000, 10000};
    uint16_t integer_part, decimal_part;
    uint8_t max_index;
    bool is_negative = false;

    if (number < 0){
        is_negative = true;
        number *=-1;
    };

    if (nr_of_decimals > 4){
        max_index = 3;
    }
    else{
        max_index = nr_of_decimals - 1;
    }

    integer_part = static_cast<uint16_t>(number);
    number       = (number - integer_part)*dec_mult[max_index];
    decimal_part = static_cast<uint16_t>(number);

    if (is_negative){
        writeCharacter('-');
    };
    writeNumber(integer_part, int_nr_of_digits);
    writeCharacter('.');
    writeNumber(decimal_part, nr_of_decimals);
}


void lcdDisplay::clearRegion(uint8_t nr_of_positions){
    // writes spaces 0x20 for number_of_position
    // set address must be called before
    uint8_t i = 0;
    while(i < nr_of_positions){
        writeCharacter(' ');
        i++;
    }
}


lcdDisplay::~lcdDisplay(){
};
