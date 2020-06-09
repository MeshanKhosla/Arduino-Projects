#include <Servo.h>
#define pot A7

int del = 1;
int rawValFromPot;
int servoOutput;

Servo myServo;

void setup() {
  Serial.begin(9600);
  myServo.attach(9);
}

void loop() {
  rawValFromPot = analogRead(pot);
  servoOutput = map(rawValFromPot, 0, 1023, 180, 0);
  Serial.println(servoOutput);
  myServo.write(servoOutput);
  delay(del);
}
