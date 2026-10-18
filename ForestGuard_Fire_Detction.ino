#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define MQ2_PIN A0

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  Serial.println("ForestGuard Fire Detection");
  Serial.println("System Started");
}
void loop() {
  int smokeValue = analogRead(MQ2_PIN);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Smoke: ");
  Serial.println(smokeValue);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  if (smokeValue > 400 || temperature > 50) {
    Serial.println("FIRE ALERT!");
  } else {
    Serial.println("Environment Normal");
  }

  delay(2000);
}
