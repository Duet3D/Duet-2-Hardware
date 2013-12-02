/*
Test code for A4982 Stepper drivers on DUET 0.3,0.40.5 and expansion board 0.1

The Vref is set first, note the peculiarity with the values reversed for Pot1 and 2 vs Pot 3 and 4, this only applies to Duet 0.3

Channel 0:  0x0 = Vref High (~1,6V), 0x100 = Vref Off, 0x80 = Vref 50% (~0.8V)
Channel 1:  0x0 = Vref High (~1,6V), 0x100 = Vref Off, 0x80 = Vref 50% (~0.8V)
Channel 2:  0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)
Channel 3:  0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)

On Duet 0.4 and later and expansion board:

Channel 0:  0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)
Channel 1:  0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)
Channel 2:  0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)
Channel 3:  0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)

This code then steps all 4 axis almost simultaneously CW then CCW slower then faster
If an expansion board is defined it add the expansion board axis into the order.

The values for delayMicroseconds work with 1/16th microstepping
extend the delays for larger microsteps.

If the end stops are not connected by a NC switch or wire short then set the relavent endStopDisabled=true
to disable the checking for them

For the E0_En and Z_EN pins the "SamNonDuePin" libaray allows access to pins that are not defined in the Arduino
Due software but are provided by the SAM3X8E, this library is still in development.

Various pins are not defined, or defined differently on the Arduino Due so the SamNonDuePin library is used to access them as standard I/O

*/
#include "Arduino.h"
#include <Wire.h>
#include "MCP4461.h"
#include "SamNonDuePin.h"

#define EXPANSION

MCP4461 mcp_duet(0x2C);

#ifdef EXPANSION
MCP4461 mcp_exp(0x2E);
#endif

//digipot resistance values
//0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)
#define E0_POT_R 0x80
#define X_POT_R 0x80 
#define Z_POT_R 0x80
#define Y_POT_R 0x80
#define E1_POT_R 0x80
#define E2_POT_R 0x80
#define E3_POT_R 0x80
#define E4_POT_R 0x80

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
#define Z_EN X1//Sam pin PC27 not defined for Due
#define Z_STOP 60

#define E0_STEP X2 //Sam pin configured for CAN on Due
#define E0_DIR X3 //Sam pin configured for CAN on Due
#define E0_EN  X0//Sam pin pin PA5 not defined for Due
#define E0_STOP 31

#ifdef EXPANSION
#define E1_STEP 41
#define E1_DIR 35
#define E1_EN  37
#define E1_STOP 24

#define E2_STEP 39
#define E2_DIR 53
#define E2_EN  X8
#define E2_STOP 46

#define E3_STEP X4
#define E3_DIR 51
#define E3_EN  50
#define E3_STOP 45

#define E4_STEP 49
#define E4_DIR 48
#define E4_EN  47
#define E4_STOP 44
#endif

//use to disable the axis endstop checking code so the motors step regardless
boolean XendStopDisabled = true;
boolean YendStopDisabled = true;
boolean ZendStopDisabled = true;
boolean E0endStopDisabled = true;
#ifdef EXPANSION
boolean E1endStopDisabled = true;
boolean E2endStopDisabled = true;
boolean E3endStopDisabled = true;
boolean E4endStopDisabled = true;
#endif

void setup() {
 //setup the Vrefs input to the stepper drivers
 //start the I2C comms with the digipot
 mcp_duet.begin();
 //set both volatile and non volatile wipers
 mcp_duet.setVolatileWiper(0,E0_POT_R);  mcp_duet.setNonVolatileWiper(0,E0_POT_R);
 mcp_duet.setVolatileWiper(1,X_POT_R);  mcp_duet.setNonVolatileWiper(1,X_POT_R);
 mcp_duet.setVolatileWiper(2,Z_POT_R);  mcp_duet.setNonVolatileWiper(2,Z_POT_R);
 mcp_duet.setVolatileWiper(3,Y_POT_R);  mcp_duet.setNonVolatileWiper(3,Y_POT_R);
 #ifdef EXPANSION
 mcp_exp.begin();
 mcp_exp.setVolatileWiper(0,E1_POT_R);  mcp_exp.setNonVolatileWiper(0,E1_POT_R);
 mcp_exp.setVolatileWiper(0,E2_POT_R);  mcp_exp.setNonVolatileWiper(0,E2_POT_R);
 mcp_exp.setVolatileWiper(0,E3_POT_R);  mcp_exp.setNonVolatileWiper(0,E3_POT_R);
 mcp_exp.setVolatileWiper(0,E4_POT_R);  mcp_exp.setNonVolatileWiper(0,E4_POT_R);
 #endif
 
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
 pinModeNonDue(Z_EN, OUTPUT);
 pinMode(Z_STOP, INPUT);
 
 pinModeNonDue(E0_STEP, OUTPUT);
 pinModeNonDue(E0_DIR, OUTPUT);
 pinModeNonDue(E0_EN, OUTPUT);
 pinMode(E0_STOP, INPUT);
#ifdef EXPANSION
 pinMode(E1_STEP, OUTPUT);
 pinMode(E1_DIR, OUTPUT);
 pinMode(E1_EN, OUTPUT);
 pinMode(E1_STOP, INPUT);
 
 pinMode(E2_STEP, OUTPUT);
 pinMode(E2_DIR, OUTPUT);
 pinModeNonDue(E2_EN, OUTPUT);
 pinMode(E2_STOP, INPUT);
 
 pinModeNonDue(E3_STEP, OUTPUT);
 pinMode(E3_DIR, OUTPUT);
 pinMode(E3_EN, OUTPUT);
 pinMode(E3_STOP, INPUT);
 
 pinMode(E4_STEP, OUTPUT);
 pinMode(E4_DIR, OUTPUT);
 pinMode(E4_EN, OUTPUT);
 pinMode(E4_STOP, INPUT);
#endif

//disable the steppers to begin
  digitalWrite(X_EN, HIGH);
  digitalWrite(Y_EN, HIGH);
  digitalWriteNonDue(Z_EN, HIGH);
  digitalWriteNonDue(E0_EN, HIGH);
#ifdef EXPANSION
  digitalWrite(E1_EN, HIGH);
  digitalWriteNonDue(E2_EN, HIGH);
  digitalWrite(E3_EN, HIGH);
  digitalWrite(E4_EN, HIGH);
#endif
}

void loop() {
  
  //enable the steppers
  digitalWrite(X_EN, LOW);
  digitalWrite(Y_EN, LOW);
  digitalWriteNonDue(Z_EN, LOW);
  digitalWriteNonDue(E0_EN, LOW);
#ifdef EXPANSION
  digitalWrite(E1_EN, LOW);
  digitalWriteNonDue(E2_EN, LOW);
  digitalWrite(E3_EN, LOW);
  digitalWrite(E4_EN, LOW);
#endif
  
  //CW 
  digitalWrite(X_DIR, HIGH);
  digitalWrite(Y_DIR, HIGH);
  digitalWrite(Z_DIR, HIGH);
  digitalWriteNonDue(E0_DIR, HIGH);
#ifdef EXPANSION
  digitalWrite(E1_DIR, HIGH);
  digitalWrite(E2_DIR, HIGH);
  digitalWrite(E3_DIR, HIGH);
  digitalWrite(E4_DIR, HIGH);
#endif
  
  for (int i = 1 ; i<5000 ;i++) { 
    if(digitalRead(X_STOP) == 0 || XendStopDisabled) digitalWrite(X_STEP, HIGH);
    if(digitalRead(Y_STOP) == 0 || YendStopDisabled) digitalWrite(Y_STEP, HIGH);
    if(digitalRead(Z_STOP) == 0 || ZendStopDisabled) digitalWrite(Z_STEP, HIGH);
    if(digitalRead(E0_STOP) == 0 || E0endStopDisabled)  digitalWriteNonDue(E0_STEP, HIGH);
#ifdef EXPANSION
    if(digitalRead(E1_STOP) == 0 || E1endStopDisabled)  digitalWrite(E1_STEP, HIGH);
    if(digitalRead(E2_STOP) == 0 || E2endStopDisabled)  digitalWrite(E2_STEP, HIGH);
    if(digitalRead(E3_STOP) == 0 || E3endStopDisabled)  digitalWriteNonDue(E3_STEP, HIGH);
    if(digitalRead(E4_STOP) == 0 || E4endStopDisabled)  digitalWrite(E4_STEP, HIGH);
#endif  
    delayMicroseconds(90);
    if(digitalRead(X_STOP) == 0 || XendStopDisabled) digitalWrite(X_STEP, LOW);
    if(digitalRead(Y_STOP) == 0 || YendStopDisabled) digitalWrite(Y_STEP, LOW);
    if(digitalRead(Z_STOP) == 0 || ZendStopDisabled) digitalWrite(Z_STEP, LOW);
    if(digitalRead(E0_STOP) == 0 || E0endStopDisabled)  digitalWriteNonDue(E0_STEP, LOW);
#ifdef EXPANSION
    if(digitalRead(E1_STOP) == 0 || E1endStopDisabled)  digitalWrite(E1_STEP, LOW);
    if(digitalRead(E2_STOP) == 0 || E2endStopDisabled)  digitalWrite(E2_STEP, LOW);
    if(digitalRead(E3_STOP) == 0 || E3endStopDisabled)  digitalWriteNonDue(E3_STEP, LOW);
    if(digitalRead(E4_STOP) == 0 || E4endStopDisabled)  digitalWrite(E4_STEP, LOW);
#endif
    delayMicroseconds(90);
  }
  //disable the steppers
  digitalWrite(X_EN, HIGH);
  digitalWrite(Y_EN, HIGH);
  digitalWriteNonDue(Z_EN, HIGH);
  digitalWriteNonDue(E0_EN, HIGH);
#ifdef EXPANSION
  digitalWrite(E1_EN, HIGH);
  digitalWriteNonDue(E2_EN, HIGH);
  digitalWrite(E3_EN, HIGH);
  digitalWrite(E4_EN, HIGH);
#endif
  
  delay(1000);
  
  //enable the steppers
  digitalWrite(X_EN, LOW);
  digitalWrite(Y_EN, LOW);
  digitalWriteNonDue(Z_EN, LOW);
  digitalWriteNonDue(E0_EN, LOW);
#ifdef EXPANSION
  digitalWrite(E1_EN, LOW);
  digitalWriteNonDue(E2_EN, LOW);
  digitalWrite(E3_EN, LOW);
  digitalWrite(E4_EN, LOW);
#endif
 
  //CCW
  digitalWrite(X_DIR, LOW);
  digitalWrite(Y_DIR, LOW);
  digitalWrite(Z_DIR, LOW);
  digitalWriteNonDue(E0_DIR, LOW);
#ifdef EXPANSION
  digitalWrite(E1_DIR, LOW);
  digitalWrite(E2_DIR, LOW);
  digitalWrite(E3_DIR, LOW);
  digitalWrite(E4_DIR, LOW);
#endif
  
  for (int i = 1 ; i<5000 ;i++)
  { 
    if(digitalRead(X_STOP) == 0 || XendStopDisabled) digitalWrite(X_STEP, HIGH);
    if(digitalRead(Y_STOP) == 0 || YendStopDisabled) digitalWrite(Y_STEP, HIGH);
    if(digitalRead(Z_STOP) == 0 || ZendStopDisabled) digitalWrite(Z_STEP, HIGH);
    if(digitalRead(E0_STOP) == 0 || E0endStopDisabled)  digitalWriteNonDue(E0_STEP, HIGH);
#ifdef EXPANSION
    if(digitalRead(E1_STOP) == 0 || E1endStopDisabled)  digitalWrite(E1_STEP, HIGH);
    if(digitalRead(E2_STOP) == 0 || E2endStopDisabled)  digitalWrite(E2_STEP, HIGH);
    if(digitalRead(E3_STOP) == 0 || E3endStopDisabled)  digitalWriteNonDue(E3_STEP, HIGH);
    if(digitalRead(E4_STOP) == 0 || E4endStopDisabled)  digitalWrite(E4_STEP, HIGH);
#endif 
    delayMicroseconds(100);
    if(digitalRead(X_STOP) == 0 || XendStopDisabled) digitalWrite(X_STEP, LOW);
    if(digitalRead(Y_STOP) == 0 || YendStopDisabled) digitalWrite(Y_STEP, LOW);
    if(digitalRead(Z_STOP) == 0 || ZendStopDisabled) digitalWrite(Z_STEP, LOW);
    if(digitalRead(E0_STOP) == 0 || E0endStopDisabled) digitalWriteNonDue(E0_STEP, LOW);
#ifdef EXPANSION
    if(digitalRead(E1_STOP) == 0 || E1endStopDisabled)  digitalWrite(E1_STEP, LOW);
    if(digitalRead(E2_STOP) == 0 || E2endStopDisabled)  digitalWrite(E2_STEP, LOW);
    if(digitalRead(E3_STOP) == 0 || E3endStopDisabled)  digitalWriteNonDue(E3_STEP, LOW);
    if(digitalRead(E4_STOP) == 0 || E4endStopDisabled)  digitalWrite(E4_STEP, LOW);
#endif
    delayMicroseconds(100);
  }
  //disable the steppers
  digitalWrite(X_EN, HIGH);
  digitalWrite(Y_EN, HIGH);
  digitalWriteNonDue(Z_EN, HIGH);
  digitalWriteNonDue(E0_EN, HIGH);
#ifdef EXPANSION
  digitalWrite(E1_EN, HIGH);
  digitalWrite(E2_EN, HIGH);
  digitalWrite(E3_EN, HIGH);
  digitalWrite(E4_EN, HIGH);
#endif
  delay(1000);
}



