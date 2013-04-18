/*
Test code for A4982 Stepper drivers on DUET 0.3

The Vref is set first, note the peculiarity with the values reversed for Pot1 and 2 vs Pot 3 and 4

This code then steps all 4 axis almost simultaneously CW then CCW slower then faster
The values for delayMicroseconds work with 1/16th microstepping
extend the delays for larger microsteps.

If the end stops are not connected by a NC switch or wire short then set the relavent endStopDisabled=true
to disable the checking for them

For the E0_En and Z_EN pins the "UdefDuePin" libaray allows access to pins that are not defined in the Arduino
Due software but are provided by the SAM3X8E, this library is still in development.

As an example all the E0 pins are switched with this alternative method (even though only E0_EN needs to be).

Three expansion header pins are assigned to E1_STEP,E1_DIR and E1_EN to demostrate communicating with off-board stepper drivers

*/
#include "Arduino.h"
#include <Wire.h>
#include "MCP4461.h"
#include "UdefDuePin.h"

MCP4461 mcp;

//digipot values
#define POT_R_1 0x55 //0x0 = Vref High (~1,6V), 0x100 = Vref Off, 0x80 = Vref 50% (~0.8V)
#define POT_R_2 0x55 //0x0 = Vref High (~1,6V), 0x100 = Vref Off, 0x80 = Vref 50% (~0.8V)
#define POT_R_3 0xAA //0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)
#define POT_R_4 0xAA //0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)

#define X_STEP 14
#define X_DIR 15
#define X_EN 29
#define X_STOP 11

#define Y_STEP 25
#define Y_DIR 26
#define Y_EN 27
#define Y_STOP 28

#define Z_STEP 5
#define Z_DIR 4
#define Z_EN 1//Undefined pin PC27
#define Z_STOP 60

#define E0_STEP 2 //68
#define E0_DIR 3 //69
#define E0_EN  0//undefined pin PA5
#define E0_STOP 4 //31

#define E1_STEP 48
#define E1_DIR 49
#define E1_EN  47
#define E1_STOP 46


//use to disable the axis endstop checking code so the motors step regardless
boolean XendStopDisabled = true;
boolean YendStopDisabled = true;
boolean ZendStopDisabled = true;
boolean E0endStopDisabled = true;
boolean E1endStopDisabled = true;

void setup() {
 //setup the Vrefs input to the stepper drivers
 //start the I2C comms with the digipot
 mcp.begin();
 //set both volatile and non volatile wipers
 mcp.setVolatileWiper(0,POT_R_1);  mcp.setNonVolatileWiper(0,POT_R_1);
 mcp.setVolatileWiper(1,POT_R_2);  mcp.setNonVolatileWiper(1,POT_R_2);
 mcp.setVolatileWiper(2,POT_R_3);  mcp.setNonVolatileWiper(2,POT_R_3);
 mcp.setVolatileWiper(3,POT_R_4);  mcp.setNonVolatileWiper(3,POT_R_4);
 
 //Setup the pins for the Stepper drivers
 pinMode(X_STEP, OUTPUT);
 pinMode(X_DIR, OUTPUT);
 pinMode(X_EN, OUTPUT);
 pinMode(X_STOP, INPUT);
 
 pinMode(Y_STEP, OUTPUT);
 pinMode(Y_DIR, OUTPUT);
 pinMode(Y_EN, OUTPUT);
 pinMode(Y_STOP, INPUT);
 
 pinMode(Z_STEP, OUTPUT);
 pinMode(Z_DIR, OUTPUT);
 pinModeUndefined(Z_EN, OUTPUT);
 pinMode(Z_STOP, INPUT);
 
 pinModeUndefined(E0_STEP, OUTPUT);
 pinModeUndefined(E0_DIR, OUTPUT);
 pinModeUndefined(E0_EN, OUTPUT);
 pinModeUndefined(E0_STOP, INPUT);
 
 pinMode(E1_STEP, OUTPUT);
 pinMode(E1_DIR, OUTPUT);
 pinMode(E1_EN, OUTPUT);
 pinMode(E1_STOP, INPUT);
 
//disable the steppers to begin
  digitalWrite(X_EN, HIGH);
  digitalWrite(Y_EN, HIGH);
  digitalWriteUndefined(Z_EN, HIGH);
  digitalWriteUndefined(E0_EN, HIGH);
  digitalWrite(E1_EN, HIGH);

}

void loop() {
  
  //enable the steppers
  digitalWrite(X_EN, LOW);
  digitalWrite(Y_EN, LOW);
  digitalWriteUndefined(Z_EN, LOW);
  digitalWriteUndefined(E0_EN, LOW);
  digitalWrite(E1_EN, LOW);
  
  //CW 
  digitalWrite(X_DIR, HIGH);
  digitalWrite(Y_DIR, HIGH);
  digitalWrite(Z_DIR, HIGH);
  digitalWriteUndefined(E0_DIR, HIGH);
  digitalWrite(E1_DIR, HIGH);
  
  for (int i = 1 ; i<5000 ;i++) { 
    if(digitalRead(X_STOP) == 0 || XendStopDisabled) digitalWrite(X_STEP, HIGH);
    if(digitalRead(Y_STOP) == 0 || YendStopDisabled) digitalWrite(Y_STEP, HIGH);
    if(digitalRead(Z_STOP) == 0 || ZendStopDisabled) digitalWrite(Z_STEP, HIGH);
    if(digitalRead(E0_STOP) == 0 || E0endStopDisabled)  digitalWriteUndefined(E0_STEP, HIGH);
    if(digitalRead(E1_STOP) == 0 || E1endStopDisabled)  digitalWrite(E1_STEP, HIGH);
    delayMicroseconds(90);
    if(digitalRead(X_STOP) == 0 || XendStopDisabled) digitalWrite(X_STEP, LOW);
    if(digitalRead(Y_STOP) == 0 || YendStopDisabled) digitalWrite(Y_STEP, LOW);
    if(digitalRead(Z_STOP) == 0 || ZendStopDisabled) digitalWrite(Z_STEP, LOW);
    if(digitalRead(E0_STOP) == 0 || E0endStopDisabled)  digitalWriteUndefined(E0_STEP, LOW);
    if(digitalRead(E1_STOP) == 0 || E1endStopDisabled)  digitalWrite(E1_STEP, LOW);
    delayMicroseconds(90);
  }
  //disable the steppers
  digitalWrite(X_EN, HIGH);
  digitalWrite(Y_EN, HIGH);
  digitalWriteUndefined(Z_EN, HIGH);
  digitalWriteUndefined(E0_EN, HIGH);
  digitalWrite(E1_EN, HIGH);
  
  delay(2000);
  
  //enable the steppers
  digitalWrite(X_EN, LOW);
  digitalWrite(Y_EN, LOW);
  digitalWriteUndefined(Z_EN, LOW);
  digitalWriteUndefined(E0_EN, LOW);
  digitalWrite(E1_EN, LOW);
 
  //CCW
  digitalWrite(X_DIR, LOW);
  digitalWrite(Y_DIR, LOW);
  digitalWrite(Z_DIR, LOW);
  digitalWriteUndefined(E0_DIR, LOW);
  digitalWrite(E1_DIR, LOW);
  
  for (int i = 1 ; i<5000 ;i++)
  { 
    if(digitalRead(X_STOP) == 0 || XendStopDisabled) digitalWrite(X_STEP, HIGH);
    if(digitalRead(Y_STOP) == 0 || YendStopDisabled) digitalWrite(Y_STEP, HIGH);
    if(digitalRead(Z_STOP) == 0 || ZendStopDisabled) digitalWrite(Z_STEP, HIGH);
    if(digitalRead(E0_STOP) == 0 || E0endStopDisabled)  digitalWriteUndefined(E0_STEP, HIGH);
    if(digitalRead(E1_STOP) == 0 || E1endStopDisabled)  digitalWrite(E1_STEP, HIGH);
    delayMicroseconds(100);
    if(digitalRead(X_STOP) == 0 || XendStopDisabled) digitalWrite(X_STEP, LOW);
    if(digitalRead(Y_STOP) == 0 || YendStopDisabled) digitalWrite(Y_STEP, LOW);
    if(digitalRead(Z_STOP) == 0 || ZendStopDisabled) digitalWrite(Z_STEP, LOW);
    if(digitalRead(E0_STOP) == 0 || E0endStopDisabled)  digitalWriteUndefined(E0_STEP, LOW);
    if(digitalRead(E1_STOP) == 0 || E1endStopDisabled)  digitalWrite(E1_STEP, LOW);
    delayMicroseconds(100);
  }
  //disable the steppers
  digitalWrite(X_EN, HIGH);
  digitalWrite(Y_EN, HIGH);
  digitalWriteUndefined(Z_EN, HIGH);
  digitalWriteUndefined(E0_EN, HIGH);
  digitalWrite(E1_EN, HIGH);
  delay(2000);
}



