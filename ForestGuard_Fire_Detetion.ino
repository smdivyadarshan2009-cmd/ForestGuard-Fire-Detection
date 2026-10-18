#include <DHT.h>
#include <SPI.h>
#include <LoRa.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define MQ2_PIN A0

// LoRa pins for Arduino + SX1278/Ra-02
#define LORA_SS 10
#define LORA_RST 9
#define LORA_DIO0 2

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa initialization failed!");
    while (true);
  }

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

  bool fireDetected = false;

  if (smokeValue > 400 || temperature > 50) {
    fireDetected = true;
  }

  LoRa.beginPacket();

  if (fireDetected) {
    LoRa.print("FIRE ALERT!");
    Serial.println("FIRE ALERT!");
  } else {
    LoRa.print("NORMAL");
    Serial.println("Environment Normal");
  }

  LoRa.print(" | Smoke: ");
  LoRa.print(smokeValue);

  LoRa.print(" | Temp: ");
  LoRa.print(temperature);

  LoRa.print(" | Humidity: ");
  LoRa.print(humidity);

  LoRa.endPacket();

  delay(5000);
}
