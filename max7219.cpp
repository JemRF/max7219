/*
* The MIT License (MIT)
*
* Copyright (c) JEMRF
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
********************************************************************************
*
* Module     : max7219.cpp
* Author     : Jonathan Evans
* Description: MAX7219 LED Display Driver
*
* The MAX7219/MAX7221 are compact, serial input/output common-cathode display drivers that interface
* microprocessors (µPs) to 7-segment numeric LED displays of up to 8 digits, bar-graph displays, or 64 
* individual LEDs
* Datasheet  : https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf
*
* Library Description
*
*  - This library implements the 7-segment numeric LED display of 8 digits 
*  - The host communicates with the MAX7219 using three signals: CLK (pin 10), CS (pin 11), DIN (pin 12). 
*  - Pins can be configured in max7219.h
*  - The MAX7219 is a SPI interface
*  - This library uses the bitbang method for communication with the MAX7219 
*
* Usage
*
* Three methods are exposed for use:
*  
*  1. Begin
*  This method initializes communication, takes the display out of test mode, clears the screen and sets intensity.
*  Intensity is set at maximum but can be configured in max7219.h
*  
*  2. DisplayChar(Digit, Value, DP)
*  This method displays a single value (character) in position DIGIT (0=right most digit, 7=left most digit)
*  
*  3. DisplayText(Text, Justify)
*  This method displays a text string (Text) either right justified (Justify=0) or left justified (Justify=1) 
*/

#include "max7219.h"

MAX7219:: MAX7219(void)
{
  pinMode(MAX_DIN, OUTPUT);
  pinMode(MAX_CS, OUTPUT);
  pinMode(MAX_CLK, OUTPUT);
}

void MAX7219::MAX7219_ShutdownStart (void)
{
  MAX7219_Write(REG_SHUTDOWN, 0);                     
}

void MAX7219:: MAX7219_DisplayTestStart (void)
{
  MAX7219_Write(REG_DISPLAY_TEST, 1);                 
}

void MAX7219::Clear(void) {
    
    for(int i=0;i<8;i++) {
        MAX7219_Write(i+1,0x00);
    }
}

void MAX7219::MAX7219_DisplayTestStop (void)
{
  MAX7219_Write(REG_DISPLAY_TEST, 0);                 
}

void MAX7219::MAX7219_SetBrightness (char brightness)
{
  brightness &= 0x0f;                                 
  MAX7219_Write(REG_INTENSITY, brightness);           
}

unsigned char MAX7219::MAX7219_LookupCode (char character, unsigned int dp)
{
  int i;
  unsigned int d=0;
 if (dp) d=1;  
  if (character>=35 && character<=44) {
    character+=13;
    d=1;
  }
  for (i = 0; MAX7219_Font[i].ascii; i++)              
    if (character == MAX7219_Font[i].ascii){
      if (d){
        d=MAX7219_Font[i].segs;
        d |= (1<<7);
        return (d);                                    
        }
      else{
        return MAX7219_Font[i].segs;                    
      }
    }
      
  return 0;                                             
}

void MAX7219::DisplayText(char *text, int justify){
  int decimal[16];
  char trimStr[16] = "";
  int x,y=0;
  int s;
  
  s=strlen(text);
  if (s>16) s=16;
  for (x=0;x<s;x++){
    if (text[x]=='.'){
      decimal[y-1]=1;
      }
    else{
      trimStr[y]=text[x];
      decimal[y]=0;
      y++;
     }
  }
  if (y>8) y=8;
  for (x=0;x<y;x++){
      if (justify==0)
        DisplayChar((int)(y-x+7-y),trimStr[x], decimal[x]);    
      if (justify==1){
        DisplayChar((int)(y-x+7-y-(8-y)),trimStr[x], decimal[x]);    
        
      }
  }
}

void MAX7219::MAX7219_Write(volatile byte opcode, volatile byte data) {
    digitalWrite(MAX_CS,LOW);
    shiftOut(MAX_DIN,MAX_CLK,MSBFIRST,opcode);
    shiftOut(MAX_DIN,MAX_CLK,MSBFIRST,data);
    digitalWrite(MAX_CS,HIGH);
}    

void MAX7219::DisplayChar(int digit, char value, bool dp) {
      MAX7219_Write(digit+1,MAX7219_LookupCode(value, dp));
}

void MAX7219::MAX7219_ShutdownStop (void)
{
  MAX7219::MAX7219_Write(REG_SHUTDOWN, 1);   
}
 
void MAX7219::Begin()
{ 
  digitalWrite(MAX_CS,HIGH);
  MAX7219_Write(REG_SCAN_LIMIT, 7);                   
  MAX7219_Write(REG_DECODE, 0x00);                    
  MAX7219_ShutdownStop();                             
  MAX7219_DisplayTestStop();                          
  Clear();                                    
  MAX7219_SetBrightness(INTENSITY_MAX);               
}
