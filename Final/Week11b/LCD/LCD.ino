#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.init();
  lcd.backlight();
}

void loop()
{
  lcd.setCursor(3, 0);
  lcd.print("Hello World");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Hallym Software");
  delay(1000);
  lcd.clear();
  delay(1000);
}