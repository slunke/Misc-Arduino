int ledpin = 4;
int buttonpin = 3;

void setup() {
  pinMode(ledpin, OUTPUT);
  pinMode(buttonpin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(buttonpin) == LOW){
    flash(3);
    delay(500);
    flash(6);
  }
}


void flash(int count){
  for (int i=0;i< count;i++){
    digitalWrite(ledpin, HIGH);
    delay(10);
    digitalWrite(ledpin, LOW);
    delay(100);
  }
}

