#include <Arduino.h>
#include <Servo.h>

#define LED 53

// KEYPAD
#define KEYPAD_1 2
#define KEYPAD_2 3
#define KEYPAD_3 4
#define KEYPAD_A 5
#define KEYPAD_B 6
#define KEYPAD_C 7
#define KEYPAD_D 8

// RFID Reader
#define RST 46
#define RFID_1 44
#define RFID_2 42
#define RFID_3 40
#define RFID_4 38
#define RFID_5 36

// SERVO
#define SERVO 9

void readCol1();
void readCol2();
void readCol3();
void waitingRaws();
void infoInput();
void bombHasBeenPlanted();
void servoSpeed(int startAngle, int stopAngle, int timeMS, Servo servo);

String logInput;
String lastInput;
String currentInput;
boolean newInput;

Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  pinMode(KEYPAD_1, OUTPUT);
  pinMode(KEYPAD_2, OUTPUT);
  pinMode(KEYPAD_3, OUTPUT);
  
  pinMode(KEYPAD_A, INPUT);
  pinMode(KEYPAD_B, INPUT);
  pinMode(KEYPAD_C, INPUT);
  pinMode(KEYPAD_D, INPUT);

  servo.attach(SERVO);
  servo.write(0);
}

void loop() {
  newInput = false;
  currentInput = "";

  readCol1();
  readCol2();
  readCol3();

  if (newInput)
  {
    infoInput();
    lastInput = currentInput;
    logInput += currentInput;
    Serial.println(lastInput + " " + logInput);
  }
  
  if (logInput.endsWith("7355608"))
  {
    logInput = "";
    bombHasBeenPlanted();
  }
  else if (logInput.endsWith("1104"))
  {
    logInput = "";
  servoSpeed(0, 150, 1000, servo);
  servoSpeed(150, 15, 2500, servo);
  servoSpeed(15, 180, 500, servo);
  }
  
}

void readCol1(){
  digitalWrite(KEYPAD_1, HIGH);
  if (digitalRead(KEYPAD_A))
  {
    newInput = true;
    currentInput += "1";
  }
  if (digitalRead(KEYPAD_B))
  {
    newInput = true;
    currentInput += "4";
  }
  if (digitalRead(KEYPAD_C))
  {
    newInput = true;
    currentInput += "7";
  }
  if (digitalRead(KEYPAD_D))
  {
    newInput = true;
    currentInput += "*";
  }
  waitingRaws();
  digitalWrite(KEYPAD_1, LOW);
}

void readCol2(){
  digitalWrite(KEYPAD_2, HIGH);
  if (digitalRead(KEYPAD_A))
  {
    newInput = true;
    currentInput += "2";
  }
  if (digitalRead(KEYPAD_B))
  {
    newInput = true;
    currentInput += "5";
  }
  if (digitalRead(KEYPAD_C))
  {
    newInput = true;
    currentInput += "8";
  }
  if (digitalRead(KEYPAD_D))
  {
    newInput = true;
    currentInput += "0";
  }
  waitingRaws();
  digitalWrite(KEYPAD_2, LOW);
}

void readCol3(){
  digitalWrite(KEYPAD_3, HIGH);
  if (digitalRead(KEYPAD_A))
  {
    newInput = true;
    currentInput += "3";
  }
  if (digitalRead(KEYPAD_B))
  {
    newInput = true;
    currentInput += "6";
  }
  if (digitalRead(KEYPAD_C))
  {
    newInput = true;
    currentInput += "9";
  }
  if (digitalRead(KEYPAD_D))
  {
    newInput = true;
    currentInput += "#";
  }
  waitingRaws();
  digitalWrite(KEYPAD_3, LOW);
}

void waitingRaws(){
  if (digitalRead(KEYPAD_A) || digitalRead(KEYPAD_B) || digitalRead(KEYPAD_C) || digitalRead(KEYPAD_D))
  {
    while (digitalRead(KEYPAD_A) || digitalRead(KEYPAD_B) || digitalRead(KEYPAD_C) || digitalRead(KEYPAD_D));
  }
}

void infoInput(){
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
}

void bombHasBeenPlanted(){
  // float f = 1.05*exp(0.0054*t+0.000871*t*t);
  // float g = 1.049*exp(0.244*t+1.764*t*t);

  float beepPerSec = 1.04865094758901 * exp(0.0000054227501208209 * 45 + 0.000000000871011529375232 * 45 * 45);
  float waitMS = 1000.0/beepPerSec-9;

  while (waitMS > 0)
  {
    digitalWrite(LED, HIGH);
    delay(waitMS/2);
    digitalWrite(LED, LOW);
    delay(waitMS/2);
    waitMS -= 10;
  }
}

void servoSpeed(int startAngle, int stopAngle, int timeMS, Servo servo){
  int deltaAngle = abs(stopAngle - startAngle);
  for (int angle = startAngle; angle <= stopAngle; angle++)
  {
    servo.write(angle);
    delay(timeMS/deltaAngle);
  }  
  for (int angle = startAngle; angle >= stopAngle; angle--)
  {
    servo.write(angle);
    delay(timeMS/deltaAngle);
  }
}
