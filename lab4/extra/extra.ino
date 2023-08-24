int led[] = { 0, D0, D1, D2, D5, D6 };
void setup() {
  // put your setup code here, to run once:
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i = 0;
  int stack = 0;
  int val = 0;
  for (i=0; i<5; i++) {
      Serial.println(i%5);
      analogWrite(led[i%5], 0);
      analogWrite(led[i%5 + 1], 51);
      analogWrite(led[i%5 + 2], 102);
      analogWrite(led[i%5 + 3], 153);
      analogWrite(led[i%5 + 4], 204);
      delay(100);
    }    
  }
