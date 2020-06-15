#include "pitches.h"
#define buzzer 5

int wrongAnswerMelody[] = {
  NOTE_D4, NOTE_D4,
};

int wrongAnswerDuration[] = {
  1, 1,
};

int rightAnswerMelody[] = {
  NOTE_A4,
};

int rightAnswerDuration[] = {
  5,
};


void playWrongAnswerSound() {
  for (int i = 0; i < sizeof(wrongAnswerMelody) / sizeof(wrongAnswerMelody[0]); i++) {
    tone(buzzer, wrongAnswerMelody[i], wrongAnswerDuration[i] * 100); // Chooses melody based on melody array for value from duration array
    delay((wrongAnswerDuration[i] * 100) + 90);
    delay(10);
  }
}

void playRightAnswerSound() {
  for (int i = 0; i < sizeof(rightAnswerMelody) / sizeof(rightAnswerMelody[0]); i++) {
    tone(buzzer, rightAnswerMelody[i], rightAnswerDuration[i] * 100); // Chooses melody based on melody array for value from duration array
    delay((rightAnswerDuration[i] * 100) + 90);
    delay(10);
  }
}
