#include <pitches.h>
#include "SR04.h"

#define TRIG_PIN 12
#define ECHO_PIN 10 
#define greenLED 4
#define redLED 2
#define buzzer 8

// Number of centimeters before Alarm goes off
int threshold = 50;
SR04 ultrasonicSensor = SR04(ECHO_PIN,TRIG_PIN);

// Distance from objects stored in a long
long distance;



void setup() {
   Serial.begin(9600);//Initialization of Serial Port
   delay(1000);
   pinMode(greenLED, OUTPUT);
   pinMode(redLED, OUTPUT);
   pinMode(buzzer, OUTPUT);
}

void loop() {
   distance = ultrasonicSensor.Distance();
//   Serial.print(distance);
//   Serial.println("cm");

// Green LED if object is less than threshold cm away; red if object > threshold cm
   if(distance > threshold) {
    analogWrite(greenLED, 255);
    analogWrite(redLED, 0);
    analogWrite(buzzer, 0);
   } else {
    analogWrite(redLED, 255);
    analogWrite(greenLED, 0);
    analogWrite(buzzer, NOTE_A4);
   }
   

}
