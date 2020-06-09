// This plays the office theme song when the breadboard is touched

#include "pitches.h"

#define led 3
#define tiltswitch 10
#define buzzer 9


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
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(tiltswitch, INPUT_PULLUP);

  analogWrite(led, 0);
  analogWrite(buzzer, 0);

}

void loop() {
  if(digitalRead(tiltswitch) == HIGH) {
    for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
      tone(buzzer, melody[i], duration[i] * 100); // Chooses melody based on melody array for value from duration array
      analogWrite(led, 100);
      delay((duration[i] * 100) + 90);
      delay(10);
    }
  }
}
