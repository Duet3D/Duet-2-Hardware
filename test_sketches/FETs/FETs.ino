/*
Test code for FET outputs on DUET 0.4
Note on 0.3 the FETS come on automatically when 12V is applied (the driver fets invert
the logic)

Uses the Undefined Arduino Due Pins Library "SamNonDuePin" to demonstrate PWM on
pins that are not defined as PWM within the DUE software but are on the SAM3X8E

Note no setup of the pins is required as this is carried out within the analogWriteUndefined()
function in the same way as it is done within the normal analogWrite() function in arduino.

On the Duet 0.3 the following pins are connected:
E0_PWM    PIO_PC8B_PWML3   // Undefined pin 5
FAN0_PWM  PIO_PC2B_PWML0   // Undefined pin 6
BED_PWM   Arduino digital pin 6

Finally I am using the option of defining the Arduino Undef pins with a X in front of them, 
this allows for easy distinguishing of them but is not required.
*/

#include "Arduino.h"
#include "SamNonDuePin.h"

#define E0_PWM X5  
#define FAN0_PWM X6 
#define BED_PWM 6 

void setup() {
}

void loop() {
  for (int i = 0 ; i<256 ;i++)
  { 
    analogWriteNonDue(FAN0_PWM, i);
    analogWriteNonDue(E0_PWM, i);
    analogWrite(BED_PWM, i);
    delay(10);
  }
  delay(500); 
  for (int i = 255 ; i>=0 ;i--)
  { 
    analogWriteNonDue(FAN0_PWM, i);
    analogWriteNonDue(E0_PWM, i);
    analogWrite(BED_PWM, i);
    delay(10);
  }
  delay(500);  
}
