#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PHOTO_PIN A0

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  // Pin init
  pinMode(PHOTO_PIN, INPUT);
  // LCD init
  lcd.init();
  lcd.backlight();
}

void loop()
{
  int value = analogRead(PHOTO_PIN);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("[ Value : ");
  lcd.print(value);
  lcd.print(" ]");
  delay(1000);
}