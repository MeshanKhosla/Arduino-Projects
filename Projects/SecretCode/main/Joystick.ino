// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

// Used to determine whether value has changed
int prev_X_Val = 9999;
int prev_Y_Val = 9999;
bool prev_button_pressed = true;

// Current values 
bool buttonPressed = false;
int x_val;
int y_val;

void setupJoystick() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);  
}

// Function that will go inside loop function
void updateJoystickValues() {
  //  Reads values from X and Y pins (0-1023)
  int raw_y_val = analogRead(Y_pin);
  int raw_x_val = analogRead(X_pin);
//  Checks value of button
  checkButtonPressed();



// Converts raw val (0-1023) to a value from (0-100)
// Default X: 51
// Default Y: 49
// Default button (Not pressed): 0
  y_val = map(raw_y_val, 0, 1023, 0, 100);
  x_val = map(raw_x_val, 0, 1023, 0, 100);
//  Instead of constantly writing to Serial, only write to serial when a value changes
  printWhenValueChanges(y_val, x_val);

}


void printWhenValueChanges(int y_val, int x_val) {
  if(y_val != prev_Y_Val || x_val != prev_X_Val || buttonPressed != prev_button_pressed) {
//    updateValuesToSerial();
    prev_Y_Val = y_val;
    prev_X_Val = x_val;
    prev_button_pressed = buttonPressed;
  }
}

void updateValuesToSerial() {
  Serial.print("Switch:  ");
  Serial.print(buttonPressed);
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(x_val);
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(y_val);
  Serial.print("\n\n");
}

void checkButtonPressed() {
  if(digitalRead(SW_pin)) {
    buttonPressed = false;
  }
  else {
    buttonPressed = true;
  }
}

bool isButtonPressed() {
  return buttonPressed;
}
