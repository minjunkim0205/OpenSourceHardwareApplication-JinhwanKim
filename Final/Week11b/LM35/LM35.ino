#define LM35_PIN A0

void setup()
{
  // Serial init
  Serial.begin(9600);
  // Pin init
  pinMode(LM35_PIN, INPUT);
}

void loop()
{
  int value = analogRead(LM35_PIN);
  float volt = (value * 5.0)/1024.0;
  float temp = volt * 100;
  Serial.print("[ Temp : ");
  Serial.print(temp);
  Serial.print(" ]\n");
  delay(1000);
}