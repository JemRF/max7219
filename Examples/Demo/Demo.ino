#include <max7219.h>

MAX7219 max7219;

void setup() {
  Serial.begin(9600);
  max7219.Begin();
}

void loop() {
  String temp;
  char temp2[8];
  int y;

  //DisplayText Demo
  max7219.DisplayText("95.67F", 1); //Right justified
  delay(3000);
  max7219.Clear();
  max7219.DisplayText("95.67F", 0); //Left justified
  delay(3000);
  max7219.Clear();

  //Counter with decimals
  //slow counter
  for (float x = 0; x < 1; x = x + 0.1) {
    temp = String(x);
    temp.toCharArray(temp2, temp.length());
    max7219.DisplayText(temp2, 1); //0=left justify 1=right justify
    Serial.println(x);
    delay(500);
  }
  //fast counter
  for (float x = 0; x < 500; x++) {
    temp = String(x);
    temp.toCharArray(temp2, temp.length());
    max7219.DisplayText(temp2, 1); //0=left justify 1=right justify
    Serial.println(x);
  }
  delay(500);

  //Display Char Demo
  max7219.Clear();
  max7219.DisplayChar(7, 'H', 0); //Position 7 is on the left of the display
  delay(500);
  max7219.DisplayChar(6, 'E', 0);
  delay(500);
  max7219.DisplayChar(5, 'L', 0);
  delay(500);
  max7219.DisplayChar(4, 'L', 0);
  delay(500);
  max7219.DisplayChar(3, 'O', 0);
  delay(500);
  max7219.DisplayChar(2, '1', 0);
  delay(500);
  max7219.DisplayChar(1, '2', 0);
  delay(500);
  max7219.DisplayChar(0, '3', 0);
  delay(500);
  max7219.Clear();
  //Count front the right
  for (int x = 0; x < 8; x++) {
    max7219.DisplayChar(x, 48 + x, 0); //48 is ASCII value for 0
    delay(500);
  }
  max7219.Clear();
  delay(500);
  //Count from the left
  for (int x = 7; x >= 0; x--) {
    max7219.DisplayChar(x, 48 + (7 - x), 0); //48 is ASCII value for 0
    delay(500);
  }
  max7219.Clear();
  //Count from the right
  for (int x = 0; x < 8; x++) {
    max7219.DisplayChar(x, 48 + x, 0); //48 is ASCII value for 0
    delay(500);
    max7219.Clear();
  }
  delay(500);
  //Count front the left
  for (int x = 7; x >= 0; x--) {
    max7219.DisplayChar(x, 48 + (7 - x), 0); //48 is ASCII value for 0
    delay(500);
    max7219.Clear();
  }
}
