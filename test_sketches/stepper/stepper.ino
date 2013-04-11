/*
Test code for A4982 Stepper drivers on DUET 0.3
Note the Vref must be set first (see the digipot test code)
The digipot code only needs to run one to set the Non Volatile
Wiper values.

This code steps the X axis CW then CCW slower then faster
The values for delayMicroseconds work with 1/16th microstepping
extend the times for larger microsteps.

X_Stop must be connected to ground for the motor to turn (e.g. by a NC endstop switch)

*/
#define X_STEP 14
#define X_DIR 15
#define X_EN 29
#define X_STOP 11

void setup() {
 pinMode(X_STEP, OUTPUT);
 pinMode(X_DIR, OUTPUT);
 pinMode(X_EN, OUTPUT);
 pinMode(X_STOP, INPUT);
 digitalWrite(X_EN, HIGH); //disable the stepper to begin
 digitalWrite(X_STOP, HIGH); //Internal pullup
}

void loop() {
  digitalWrite(X_EN, LOW); //enable
  digitalWrite(X_DIR, HIGH);
  //CW steps
  for (int i = 1 ; i<5000 ;i++)
  { 
    if(digitalRead(X_STOP) == 0)
    {
      digitalWrite(X_STEP, HIGH);
      delayMicroseconds(200);
      digitalWrite(X_STEP, LOW);
      delayMicroseconds(200);
    }
  }
  digitalWrite(X_EN, HIGH); //disable
  delay(2000);
  digitalWrite(X_EN, LOW); //enable
  digitalWrite(X_DIR, LOW);
  //CCW steps
  for (int i = 1 ; i<5000 ;i++)
  { 
    if(digitalRead(X_STOP) == 0)
    {
     digitalWrite(X_STEP, HIGH);
     delayMicroseconds(50);
     digitalWrite(X_STEP, LOW);
     delayMicroseconds(50);
    }
  }
  digitalWrite(X_EN, HIGH); //disable
  delay(2000);
}
