#include "pitches.h"

#define redLED 2
#define blueLED  3
#define greenLED  4
#define yellowLED  5
#define whiteLED  6
#define buzzer  8
#define onButton 12

int melody[] = {
  NOTE_D5, NOTE_G4, NOTE_D5, NOTE_D5, NOTE_G4, NOTE_D5, NOTE_FS4, NOTE_D5,
  NOTE_D5, NOTE_FS4, NOTE_E5, NOTE_G4, NOTE_E5, NOTE_E5, NOTE_G4, NOTE_C5,
  NOTE_C5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_G4, NOTE_G5,
   
  
};


// Every value will be multiplied by 100 for length of duration
int duration[] = {
  1, 1, 7, 1, 1, 1, 1, 7,
  1, 1, 1, 1, 7, 1, 1, 3,
  3, 1, 1, 1, 1, 7, 7,
};


void setup() {
  Serial.begin(9600);
  // LED Pins
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(whiteLED, OUTPUT);

  // Buttons
  pinMode(onButton, INPUT_PULLUP);

}



bool on = false;

void loop() {
  if (digitalRead(onButton) == LOW) {
    on = true;
    Serial.println(on);
  }
  

  if (on) {
    for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
      tone(buzzer, melody[i], duration[i] * 100); // Chooses melody based on melody array for value from duration array
      LEDColor(melody[i]);
      delay((duration[i] * 100) + 90);
      turnAllLEDsOff();
      delay(10);
    }
  }
}

// Changes LED based on Note
void LEDColor(int mel) {
  if (mel == NOTE_FS4) {
    analogWrite(redLED, 255);
  }
  else if (mel == NOTE_G4) {
    analogWrite(blueLED, 255);
  }
  else if (mel == NOTE_D5) {
    analogWrite(greenLED, 255);
  }
  else if (mel == NOTE_E5) {
    analogWrite(yellowLED, 255);
  }
  else {
    analogWrite(whiteLED, 255);
  }
}

// Resets all LEDs when note occurs
void turnAllLEDsOff() {
  analogWrite(redLED, 0);
  analogWrite(blueLED, 0);
  analogWrite(greenLED, 0);
  analogWrite(yellowLED, 0);
  analogWrite(whiteLED, 0);
}
