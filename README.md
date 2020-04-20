# max7219
A library for the MAX7219 7 segment 8 digit display with decimals.


![MAX8219 Connected to Arduino UNO](https://github.com/JemRF/max7219/blob/master/pictures/MAX7219%20and%20Arduino.jpg)

An easy to use library that allows you to write to the display, using the DisplayText method. 

DisplayText(Text, Justification)
Text : The text you want to display (8 charachrts or less, plus up to 8 decimals)
Justification : Left or right justified. LEFT(0) or RIGHT(1). 

e.g.:
max7219.DisplayText("HELLO", LEFT);

Including decimals in the text will automatically take care of decimals like this:

e.g.
max7219.DisplayText("96.78F", RIGHT);

Write to specific digits on the display using the DisplayChar method:

DiaplayChar(Digit, Char, Decimal)
Digit : represents the digit number 0-7 (Rightmost Digit = 7, Leftmost Digit = 0)
Char : The character to display
Decimal : A flag to illuminate the decimal (true/false)

e.g.
max7219.DisplayChar(5, 'L', false);

Easily create your own fonts and symbols

*********************************************************************************************************
* LED Segments:         a
*                     ----
*                   f|    |b
*                    |  g |
*                     ----
*                   e|    |c
*                    |    |
*                     ----  o dp
*                       d
*   Register bits:
*      bit:  7  6  5  4  3  2  1  0
*           dp  a  b  c  d  e  f  g
*********************************************************************************************************
* Example : The letter 'I' is represented by illuminating LED's 'b' and 'c' (refer above diagram)
*           Therfore the binary representation of 'I' is as follows
*
*           abcdefg
*           0110000
* 
*           The table below contains all the binary values for the desired font. New font characters
*           can be added or altered as required. 
*           
*           The DP bit is used to switch on the decimal place LED. DP is not included in the below table
*           but is added in the register within the libary depending on the content being displayed.  
*********************************************************************************************************
