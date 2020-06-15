// Define Connections to 74HC595 (Shift register)
#define latchPin 10
#define clockPin 11
#define dataPin 9

// Patterns for characters 0,1,2,3,4,5,6,7,8,9,A,b,C,d,E,F
int dataArray[16] = {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110, B11101110, B00111110, B10011100, B01111010, B10011110, B10001110};

// Map of every character's index in dataArray, assigned in setupSevenSegmentDisplay
/* ie:
 *  'A': 10, (First value after 9 on 7 segment display)
 *  'B': 11
 *  'C': 12 
 *  ...
 */
std::map<char, int> charToNum; 

void setupSevenSegmentDisplay()
{
  // Setup pins as Outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  //  Maps the character that is passed in to the appropriate index of dataArray
  char letters[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
  int curLetterVal = 10;
  
  for(int i = 0; i < sizeof(letters) / sizeof(letters[0]); i++) {
    charToNum[letters[i]] = curLetterVal;
    curLetterVal++;
  }
}


// Takes in character value and displays it on 7 segment display. Or converts it into integer and displays int vlaue
void displayValue(char charVal) {
// Necessary to ensure output doesn't display without being complete
  digitalWrite(latchPin, LOW);

// Uses charToNum map to display letter values
  if(charVal == 'A' || charVal == 'B' || charVal == 'C' || charVal == 'D' || charVal == 'E' || charVal == 'F'){
    shiftOut(dataPin, clockPin, MSBFIRST, dataArray[charToNum[charVal]]);
  }
// For number, *, and #
  else {
//  Casting to (int) converts to ASCII. Subtracting 48 returns regular int val
    int intVal = (int)charVal - 48;
//  Asterisk: -6 -- will display as Decimal Point
    if(intVal == -6) {
      shiftOut(dataPin, clockPin, MSBFIRST, B00000001);
    }
//  Pound = -13 -- Will clear display
    else if(intVal == -13) {
      shiftOut(dataPin, clockPin, MSBFIRST, B00000000);
    }
    else {
//    Displays all numbers (Not a letter, pound, or asterisk
      shiftOut(dataPin, clockPin, MSBFIRST, dataArray[intVal]);
    }
  }
 
  // ST_CP HIGH change LEDs (To actually display number)
  digitalWrite(latchPin, HIGH);
}
