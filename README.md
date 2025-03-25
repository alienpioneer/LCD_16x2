# LCD_16x2
16x2 lcd screen library for Arduino and MSP430 using the HD44780U display driver.

# Basic Usage
Call the constructor by passing the pin mappings as arguments, then call setup() at startup.
To display a character on the screen, call setPosition() then either writeText() or writeNumber() / writeFloatNumber(). The limit is 5 digits for integers, and for float numbers 5 digits for the integer part and 4 for the decimals (ex 01234.1234).
