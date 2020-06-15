#include <ArduinoSTL.h>
#include <map>

#define blueLED 12
#define redLED 6
#define greenLED 8

const char CORRECT_SEQUENCE[] = {'1', '2', 'A', 'B'};
char userSequence[4] = {'-', '-', '-', '-'};

void setup() {
  Serial.begin(9600);
  setupSevenSegmentDisplay();
  setupJoystick();
  setupMotor();
  restartUserSequence();
}

void loop() {

  char curKey = getKeypadInput();
  //  Display pressed key on 7 segment display
  displayValue(curKey);

  updateJoystickValues();
  updateUserInput(curKey);


  //  Serial.print('{');
  //  Serial.print(userSequence[0]);
  //  Serial.print(',');
  //  Serial.print(userSequence[1]);
  //  Serial.print(',');
  //  Serial.print(userSequence[2]);
  //  Serial.print(',');
  //  Serial.print(userSequence[3]);
  //  Serial.print('}');
  //  Serial.println(" ");

  //  Check for equal arrays
  bool matching = sequencesMatch();

  // When joystick button is pressed, check if the sequence is correct. If it is, continue with green LED and motor. If not, red LED
  if (isButtonPressed()) {
    if (matching) {
      analogWrite(greenLED, 100);
      analogWrite(redLED, 0);
      playRightAnswerSound();
      // Enter time to run motor in milliseconds
      runMotor(5000);
      resetAfterAnswer();

    } else {
      analogWrite(redLED, 100);
      analogWrite(greenLED, 0);
      playWrongAnswerSound();
      delay(500);
      //    To auto-reset after getting answer wrong
      resetAfterAnswer();
      analogWrite(redLED, 0);
      restartUserSequence();
    }
  }

  // Check if user array has 4 characters. Light up blue LED if it does
  bool enteredFourCharacters = checkCharacterCount();
  if (enteredFourCharacters) {
    analogWrite(blueLED, 100);
  }
  else {
    analogWrite(blueLED, 0);
  }


  // Restart sequence -- Pound is restart button
  if (curKey == '#') {
    restartUserSequence();
    analogWrite(redLED, 0);
    analogWrite(greenLED, 0);
  }
}


void updateUserInput(char key) {
  // Does nothing unless key is one on the keypad
  if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == 'A' || key == 'B' || key == 'C' || key == 'D' || key == 'E' || key == 'F' || key == '0' || key == '*') {
    // Finds the first '-' in userSequence
    int firstIndexOfDash = 0;
    while (userSequence[firstIndexOfDash] != '-') {
      firstIndexOfDash++;

      /*  Exit while loop when pointer is at length of array (no dashes found)
           ie:
           Length of array: 4, making last index: 3
           If firstIndexOfDash is at 4, then there is no dashes present in array b/c firstIndexOfDash is past the final element index
           Changes firstIndexOfDash to -1 to show that there are no dashes present in array
           (sizeof(userSequence) / sizeof(userSequence[0]) is the length of array
      */
      if (firstIndexOfDash == (sizeof(userSequence) / sizeof(userSequence[0]))) {
        firstIndexOfDash = -1;
        break;
      }
    }
    // Sets value of key to first instance of dash in userSequence
    //  Second part of for loop is to make sure current value is not the same as last. Fixes problem with updating but does not allow same values to be in sequence
    if (firstIndexOfDash != -1 && key != userSequence[firstIndexOfDash - 1]) {
      userSequence[firstIndexOfDash] = key;
    }
  }
}

// Sets every value of userSequence to '-' (default values);
void restartUserSequence() {
  for (int i = 0; i < sizeof(userSequence) / sizeof(userSequence[0]); i++) {
    userSequence[i] = '-';
  }
}

bool sequencesMatch() {
  for (int i = 0; i < sizeof(userSequence) / sizeof(userSequence[0]); i++) {
    if (userSequence[i] != CORRECT_SEQUENCE[i]) {
      return false;
    }
  }
  return true;
}

// If userSequence contains a '-', meaning it is not complete, return false
bool checkCharacterCount() {
  for (int i = 0; i < sizeof(userSequence) / sizeof(userSequence[0]); i++) {
    if (userSequence[i] == '-') {
      return false;
    }
  }
  return true;
}

// Turns everything off after answer is entered to reset
void resetAfterAnswer() {
  analogWrite(greenLED, 0);
  analogWrite(redLED, 0);
  restartUserSequence();
}
