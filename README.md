# LCD_16x2
16x2 lcd screen library for Arduino using the HD44780U display driver.

# Basic Usage
Call the constructor when creation the object by passing the pin mappings as arguements, the call setup() at startup.
To display something on the screen, call setPosition() then either writeText() or writeNumber/writeFloatNumber(). To display integer numbers the limit is 5 digits, and for float numbers 5 digits for the integer part and 4 for the decimals (ex 01234.1234).
