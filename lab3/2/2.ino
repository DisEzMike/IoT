#include "DHT.h"
#define DHTPIN D3
#define DHTTYPE DHT11
#define LED1 D1
#define LED2 D2
#define LDR A0
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LDR, INPUT);  
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
}
void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
  int ldr = analogRead(LDR);
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  if (ldr < 100) {
    digitalWrite(LED1, HIGH);
  } else {
    digitalWrite(LED1, LOW);
  }

  if (t > 25.00) digitalWrite(LED2, HIGH);
  else digitalWrite(LED2, LOW);

  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println(ldr);
}