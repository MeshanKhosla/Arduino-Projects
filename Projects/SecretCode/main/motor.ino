#define speedPin 4
#define dir1 3
#define dir2 7

int mSpeed = 255;

void setupMotor() {
  pinMode(speedPin, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  digitalWrite(dir1, HIGH);
  digitalWrite(dir2, LOW);
}

void runMotor(int duration) {
  analogWrite(speedPin, mSpeed);
  delay(duration);
  analogWrite(speedPin, 0);
}
