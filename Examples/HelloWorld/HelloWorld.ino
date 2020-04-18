#include <max7219.h>
#define LEFT 0
#define RIGHT 1

MAX7219 max7219;

void setup() {
  Serial.begin(9600);
  max7219.Begin();
}

void loop() {
  //Display HELLO right justified
  max7219.Clear();
  max7219.DisplayText("HELLO", RIGHT);
  delay(1000);

  //Display HELLO left justified
  max7219.Clear();
  max7219.DisplayText("HELLO", LEFT);
  delay(1000);

  //Display decimals right justified
  max7219.Clear();
  max7219.DisplayText("87.56F", RIGHT);
  delay(1000);

  //Display decimals left justified
  max7219.Clear();
  max7219.DisplayText("87.56F", LEFT);
  delay(1000);
}
