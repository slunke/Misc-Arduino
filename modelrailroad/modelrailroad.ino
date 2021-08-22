

const int sensor1pin = A0;
const int sensor2pin = A1;
const int sensor3pin = A2;
const int sensor4pin = A3;

const int signal1red = 1;
const int signal1yellow1 = 2;
const int signal1yellow2 = 3;
const int signal1green = 4;

//same for signal 2 to signal 4

void setup() {
  // put your setup code here, to run once:
  pinMode(sensor1pin, INPUT);
  pinMode(sensor2pin, INPUT);
  pinMode(sensor3pin, INPUT);
  pinMode(sensor4pin, INPUT);

  pinMode(signal1red, OUTPUT);
  pinMode(signal1yellow1, OUTPUT);
  pinMode(signal1yellow2, OUTPUT);
  pinMode(signal1green, OUTPUT);

  
}

void loop() {
  // put your main code here, to run repeatedly:
  /*signal1aspect(1);
  delay(1000);
  signal1aspect(2);
  delay(1000);
  signal1aspect(3);
  delay(1000);
  signal1aspect(4);
  delay(1000);*/

  if (digitalRead(sensor1pin) == HIGH){
    signal1aspect(1);
    signal2aspect(2);
    signal3aspect(3);
    signal4aspect(4);
  }
  if (digitalRead(sensor2pin) == HIGH){
    signal1aspect(4);
    signal2aspect(1);
    signal3aspect(2);
    signal4aspect(3);
  }
  if (digitalRead(sensor3pin) == HIGH){
    signal1aspect(3);
    signal2aspect(4);
    signal3aspect(1);
    signal4aspect(2);
  }
  if (digitalRead(sensor4pin) == HIGH){
    signal1aspect(2);
    signal2aspect(3);
    signal3aspect(4);
    signal4aspect(1);
  }
}


void signal1aspect(int aspect){
  //red = 1
  //yellow = 2
  //dobble yellow = 3
  //green = 4
  if (aspect == 1){
    digitalWrite(signal1red, HIGH);
    digitalWrite(signal1yellow1, LOW);
    digitalWrite(signal1yellow2, LOW);
    digitalWrite(signal1green, LOW);
  }
  if (aspect == 2){
    digitalWrite(signal1red, LOW);
    digitalWrite(signal1yellow1, HIGH);
    digitalWrite(signal1yellow2, LOW);
    digitalWrite(signal1green, LOW);
  }
  if (aspect == 3){
    digitalWrite(signal1red, LOW);
    digitalWrite(signal1yellow1, HIGH);
    digitalWrite(signal1yellow2, HIGH);
    digitalWrite(signal1green, LOW);
  }
  if (aspect == 4){
    digitalWrite(signal1red, LOW);
    digitalWrite(signal1yellow1, LOW);
    digitalWrite(signal1yellow2, LOW);
    digitalWrite(signal1green, HIGH);
  }

}
void signal2aspect(int aspect){
  
}
void signal3aspect(int aspect){
  
}
void signal4aspect(int aspect){
  
}
