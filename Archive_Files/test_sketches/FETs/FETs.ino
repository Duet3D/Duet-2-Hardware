/*
Test code for FET outputs on DUET v0.4/v0.5 and expansion board v0.1
Note on 0.3/0.4 the FETS come on automatically when 12V is applied (the driver fets invert
the logic)

On version 0.5 and expansion board v0.1 the fet logic is inverted.

Uses the Undefined Arduino Due Pins Library "SamNonDuePin" to demonstrate PWM on
pins that are not defined as PWM within the DUE software but are on the SAM3X8E

Note no setup of the pins is required as this is carried out within the analogWriteUndefined()
function in the same way as it is done within the normal analogWrite() function in arduino.

the following pins are connected:
E0_PWM    PIO_PC8B_PWML3   // Undefined pin 5
FAN0_PWM  PIO_PC2B_PWML0   // Undefined pin 6
BED_PWM   Arduino digital pin 6
E1_PWM  PIO_PC6B_PWML2   // Undefined pin 7
E2_PWM  Arduino digital pin 9
E3_PWM  Arduino digital pin 8
E4_PWM  Arduino digital pin 7

Finally I am using the option of defining the Arduino Undef pins with a X in front of them, 
this allows for them to be more easily distinguised from arduino pins.
*/

#define EXPANSION

#include "Arduino.h"
#include "SamNonDuePin.h"

#define E0_PWM X5  
#define FAN0_PWM X6 
#define BED_PWM 6
#ifdef EXPANSION
#define E1_PWM X7
#define E2_PWM 9
#define E3_PWM 8
#define E4_PWM 7
#endif

void setup() {
}

void loop() {
  for (int i = 0 ; i<256 ;i++)
  { 
    analogWriteNonDue(FAN0_PWM, i);
    analogWriteNonDue(E0_PWM, i);
    analogWrite(BED_PWM, i);
#ifdef EXPANSION
    analogWriteNonDue(E1_PWM, i);
    analogWrite(E2_PWM, i);
    analogWrite(E3_PWM, i);
    analogWrite(E4_PWM, i);
#endif    
    delay(10);
  }
  delay(500); 
  for (int i = 255 ; i>=0 ;i--)
  { 
    analogWriteNonDue(FAN0_PWM, i);
    analogWriteNonDue(E0_PWM, i);
    analogWrite(BED_PWM, i);
#ifdef EXPANSION
    analogWriteNonDue(E1_PWM, i);
    analogWrite(E2_PWM, i);
    analogWrite(E3_PWM, i);
    analogWrite(E4_PWM, i);
#endif    
    delay(10);
  }
  delay(500);  
}
