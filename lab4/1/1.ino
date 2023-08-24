#define LDRpin A0
#define LEDpin D1

void setup() {
  pinMode(LDRpin, INPUT);
  pinMode(LEDpin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int ldr = analogRead(LDRpin);
  Serial.println(ldr);
  // if (ldr < 100) analogWrite(LEDpin, 0);/
  analogWrite(LEDpin, map(ldr, 0, 1023, 0, 255));
  delay(100);
}
