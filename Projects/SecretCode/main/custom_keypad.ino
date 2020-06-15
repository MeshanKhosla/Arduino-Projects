#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the two-dimensional array on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {29, 31, 33, 35}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {37, 39, 41, 43}; //connect to the column pinouts of the keypad


//initialize an instance of class NewKeypad
Keypad myKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

char getKeypadInput() {
  //  Gets key pressed on keypad
  char keyPressed = myKeypad.getKey();
  if(keyPressed) {
    return keyPressed;
  }
}


 
