#define LED D1
#define LDR A0

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);
  Serial.begin(9600);
}

void loop() {
  int adc = analogRead(LDR);
  Serial.print("ADC : ");
  Serial.println(adc);
  if (adc > 400) digitalWrite(LED, LOW);
  else digitalWrite(LED, HIGH);
}