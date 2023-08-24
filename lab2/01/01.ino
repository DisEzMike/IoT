#define LED D1

int state;

void checkState() {
  if (state == 1) {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  } else {
    digitalWrite(LED, LOW);
  }
}

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  if (Serial.available() > 0) {
    char a = Serial.read();
    if (a == 'a') {
      state = 1;
    } else if (a == 'b') {
      state = 0;
    }
  }

  checkState();
}