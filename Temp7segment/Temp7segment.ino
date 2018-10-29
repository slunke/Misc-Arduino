#include <OneWire.h>
#include <DallasTemperature.h>

// define OneWire object for our DS18B20 temperature sensor
OneWire ds(8);
DallasTemperature sensor(&ds);
DeviceAddress SensorAddress; //For å lagre adressen til sensoren
float tempC; //Temperature in Celsius xx.x
int inttemp = 0; //Temparature in Celsius in tenths
long lastread = 0;
int endDigit = 11;

int digit1 = 7; //PWM Display pin 12
int digit2 = 4; //PWM Display pin 9
int digit3 = 3; //PWM Display pin 8
int digit4 = A5; //PWM Display pin 6

int segA = 6; //Display pin 11
int segB = 2; //Display pin 7
int segC = A3; //Display pin 4
int segD = A1; //Display pin 2
int segE = A0; //Display pin 1
int segF = 5; //Display pin 10
int segG = A4; //Display pin 5
int segDP = A2; //Display pin 3



void setup() {
  //Set up DS18B20 temp sensor
  sensor.begin();
  sensor.getAddress(SensorAddress, 0);
  sensor.setResolution(SensorAddress, 10);
  sensor.setWaitForConversion(false);
  sensor.requestTemperatures();
  delay(750);

  //Set up pins used for 7segment
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(segDP, OUTPUT);

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);

}

void loop() {
  if (millis() - lastread > 1000){ //Read temperature every second 
    tempC = sensor.getTempC(SensorAddress);
    displayNumber(inttemp); //Refresh display to reduce flickering
    inttemp = tempC * 10;
    lastread = millis();
    ds.reset();
    displayNumber(inttemp); //Refresh display to reduce flickering
    sensor.requestTemperatures();
  }
  displayNumber(inttemp);
}


/*
 Code for 7segment adapted from code made by:
 Spark Fun Electronics 2011
 Nathan Seidle
 
 This code is public domain but you buy him a beer if you use this and you meet 
 someday (Beerware license).
*/

void displayNumber(int toDisplay) {
#define DISPLAY_BRIGHTNESS  200

#define DIGIT_ON  HIGH
#define DIGIT_OFF  LOW

  long beginTime = millis();
  if (toDisplay < 0){
    endDigit = 12;
  }else{
    endDigit = 11;
  }
  toDisplay = abs(toDisplay);

  for(int digit = 4 ; digit > 0 ; digit--) {

    //Turn on a digit for a short amount of time
    switch(digit) {
    case 1:
      digitalWrite(digit1, DIGIT_ON);
      digitalWrite(segDP, HIGH);
      lightNumber(toDisplay % 10);
      toDisplay /= 10;
      break;
    case 2:
      digitalWrite(digit2, DIGIT_ON);
      digitalWrite(segDP, LOW);
      lightNumber(toDisplay % 10);
      toDisplay /= 10;
      break;
    case 3:
      digitalWrite(digit3, DIGIT_ON);
      digitalWrite(segDP, HIGH);
      lightNumber(toDisplay % 10);
      toDisplay /= 10;
      break;
    case 4:
      digitalWrite(digit4, DIGIT_ON);
      digitalWrite(segDP, HIGH);
      lightNumber(endDigit);//Display a capital C (if positive) or negative sign (if negative)
      break;
    }

    delayMicroseconds(DISPLAY_BRIGHTNESS); 
    //Display digit for fraction of a second (1us to 5000us, 500 is pretty good)

    //Turn off all segments
    lightNumber(10); 

    //Turn off all digits
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);
  }

  while( (millis() - beginTime) < 10) ; 
  //Wait for 10ms to pass before we paint the display again
}

//Given a number, turns on those segments
//If number == 10, then turn off number
//If number == 11, turn on a capital C
//If number == 12, turn on a negative sign (-)
void lightNumber(int numberToDisplay) {

#define SEGMENT_ON  LOW
#define SEGMENT_OFF HIGH

  switch (numberToDisplay){

  case 0:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 1:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 2:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 3:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 4:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 5:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 6:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 7:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 8:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 9:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 10:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 11:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 12:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;
  }
}

