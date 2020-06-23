/*
   Touchless cubing timer
   Uses an ultrasonic sensor to detect movement
   Determines if user is getting ready to solve or has finished a solve
   Displays running time, and final time
   Stores final time in a vector (Up to 5 values) for the Average of 5 (Ao5)
   Has an erase last solve button in case of an error
*/

#include <ArduinoSTL.h>
#include <StopWatch.h>
#include <LiquidCrystal.h>
#include "SR04.h"

//Stopwatch
StopWatch stopwatch;

// Ultrasonic sensor pins
#define TRIG_PIN 23
#define ECHO_PIN 25
// Button in case user wants to delete last solve (DNF/timer error)
#define DELETE_LAST_SOLVE_BUTTON 30

// Vector to store times for the Ao5 display
std::vector<double> solveTimes;

// Initialize LCD display
// RS, E, D, D4-D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int THRESHOLD = 50; // Number of centimeters to hand needs to be to detect
const double BUFFER = 0.5; // Minimum seconds needed to count as a solve -- Prevents accidental stops of clock

// Sensor initialization. Needs to be initialized outside of setup or 'No matching function call to SR04' error will be thrown

SR04 ultrasonicSensor = SR04(ECHO_PIN, TRIG_PIN);


bool inRange;          // Determines whether a hand is in range of sensor
int inRangeCounter;    // How many times a hand has been in range of sensor
bool isSolving;        // If user is currently solving

void setup() {
  Serial.begin(9600);
  ultrasonicSensor = SR04(ECHO_PIN, TRIG_PIN);
  // 16x2 display (16 columns, 2 rows)
  lcd.begin(16, 2);
  pinMode(DELETE_LAST_SOLVE_BUTTON, INPUT_PULLUP);

  // Initalize all variables are default values
  inRangeCounter = 0;
  isSolving = false;
  inRange = false;
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
}


void loop() {
  checkButton();
  bool isClear = false;       // States that the LCD needs to be cleared during current solve
  int distance = ultrasonicSensor.Distance();

  // When hand is in range, set inRange to true and increment counter
  if (distance < THRESHOLD && distance ) {
    inRange = true;
    inRangeCounter++;
  } else {
    inRange = false;
  }

  // Start of Get Ready Stage
  // Odd counter means user is about to start solve.
  while (inRange && inRangeCounter % 2 == 1) {
    // Clears screen once per solve. This stops the flickering from constantly clearing screen.
    if (!isClear) {
      lcd.clear();
      isClear = true;
    }

    printGetReady(); // Get ready text

    /* Start of solve, exits while loop
       Saying that when hand is no longer in range, start the solve
       Can't use !inRange because inRange or distance isn't updated in this while loop
    */
    if (ultrasonicSensor.Distance() > THRESHOLD) {
      inRange = false;
      stopwatch.start();
      isSolving = true;                          // Triggers next if statement
    }
  }
  // End of Get Ready stage, solving begins


  // Currently solving
  if (isSolving) {
    double currentSolveTime = stopwatch.ms() / 1000;
    printTime(currentSolveTime);    // Prints current time to LCD display

    // Even counter means solve is over
    if (inRange && inRangeCounter % 2 == 0 && currentSolveTime > BUFFER) { // Won't count the solve if user accidentally stops clock (Less than buffer time)
      updateSolve(currentSolveTime);
      stopwatch.stop();

      //      Prints solves to Serial
      for (int i = 0; i < solveTimes.size(); i++) {
        Serial.println(solveTimes[i]);
      }
      Serial.println(" ");

      isSolving = false;
      delay(2000);                      // Delay is necessary otherwise stopwatch will start automatically -- enough time for hand to get out of way
      stopwatch.restart();
    }
  }
}
// End of loop



// If the button is pressed, remove last element of solveTimes
void checkButton() {
  if (digitalRead(DELETE_LAST_SOLVE_BUTTON) == LOW) {
    solveTimes.pop_back();
    delay(200);                      // Small delay so that there are no accidental double presses
  }
}
// Pushes the solve time to a vector and calculates the Average of 5
void updateSolve(float solveTime) {
  solveTimes.push_back(solveTime);
  double total = 0;

  // Finds Ao5 if there are 5 elements in vector
  if (solveTimes.size() == 5) {
    double minValue = *std::min_element(solveTimes.begin(), solveTimes.end());
    double maxValue = *std::max_element(solveTimes.begin(), solveTimes.end());

    // Removes slowest and fastest solves
    std::remove(solveTimes.begin(), solveTimes.end(), minValue);
    std::remove(solveTimes.begin(), solveTimes.end(), maxValue);

    // Average is found by removing fastest and slowest solve, then averaging middle 3 solves
    for (int i = 0; i < 3; i++) {
      total += solveTimes[i];
    }

    //  Prints average onto LCD display
    double avg = total / 3;     
    lcd.setCursor(3, 1);
    lcd.print("Ao5: ");
    lcd.setCursor(8, 1);
    lcd.print(avg);
    solveTimes.clear();               // Reset vector when Ao5 is complete
  }

}

void printGetReady() {
  lcd.setCursor(6, 0);
  lcd.print("Get");
  lcd.setCursor(5, 1);
  lcd.print("Ready!");
}

void printTime(double curTime) {
  lcd.setCursor(5, 1);
  lcd.print("      ");      // Gets rid of "Ready" on bottom row
  lcd.setCursor(5, 0);
  lcd.print(curTime);       // Prints time from stopwatch
}
