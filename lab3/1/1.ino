#define LED1 D1
#define LED2 D2
#define LED3 D5

#define SW D6

bool state = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(SW, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int btn = digitalRead(SW);
  if (btn == 1) {
    if (state) {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      delay(1000);
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);      
    } else {
      digitalWrite(LED1, HIGH);
      delay(1000);
      digitalWrite(LED1, LOW);       
      delay(1000);
      digitalWrite(LED2, HIGH);
      delay(1000);
      digitalWrite(LED2, LOW);       
      delay(1000);
      digitalWrite(LED3, HIGH);
      delay(1000);
      digitalWrite(LED3, LOW);       
    }
      state = !state;
  }
}
