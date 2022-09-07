// libraries
#include <LiquidCrystal.h>

// pin definitions (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(22, 24, 52, 50, 48, 46);

void setup() 
{
  // set up the LCD's number of columns and rows (column, row) counting from 1
  lcd.begin(16, 2);

  // clear the screen
  lcd.clear();
}

void loop() 
{
  // print a message to the LCD.
  lcd.print("Hello world!");

  // print on the next line (column, line) counting from 0
  lcd.setCursor(0, 1);
  lcd.print("LCD Tutorial");

  // reset to first line before looping
  lcd.setCursor(0, 0);
}
