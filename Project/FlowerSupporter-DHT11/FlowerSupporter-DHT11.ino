#include <DHT11.h>

#define DHT11_PIN 14

DHT11 dht(DHT11_PIN);

void setup()
{
  // Serial init
  Serial.begin(9600);
}

void loop()
{
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();

  Serial.print("Temp : ");
  Serial.print(temp);
  Serial.print(", Humi : ");
  Serial.print(humi);
  Serial.print("\n");

  delay(200);
}
