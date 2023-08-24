#define LED1 D1
#define LED2 D2
#define LED3 D5

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED1, HIGH);
  delay(500);
  digitalWrite(LED1, LOW);
  delay(500);

  digitalWrite(LED2, HIGH);
  delay(500);
  digitalWrite(LED2, LOW);
  delay(500);

  digitalWrite(LED3, HIGH);
  delay(500);
  digitalWrite(LED3, LOW);
  delay(500);
}
