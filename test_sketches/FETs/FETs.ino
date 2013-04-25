/*
Test code for FET outputs on DUET 0.3
Note on 0.3 the FETS come on automatically when 12V is applied (the driver fets invert
the logic)

Uses the Undefined Arduino Due Pins Library "UdefDuePin.h" to demonstrate PWM on
pins that are not defined as PWM within the DUE software but are on the SAM3X8E

Note no setup of the pins is required as this is carried out within the analogWriteUndefined()
function in the same way as it is done within the normal analogWrite() function in arduino.

On the Duet 0.3 the following pins are connected:
E0_PWM    PIO_PC8B_PWML3   // Undefined pin 5
FAN0_PWM  PIO_PC9B_PWMH3   // Undefined pin 6
BED_PWM   PIO_PB14B_PWMH2  // Undefined pin 7

E0_PWM and FAN0_PWM are connected to the same channel and are the compliment of each other
(when E0_PWM is set to 254 it is on, when FAN0_PWM is fet to 254 it is off)

Duet 0.4 will use only PWMLX pins and not connect the same channel to two pins!

Finally I am using the option of defining the Arduino Undef pins with a X in front of them, 
this allows for easy distinguishing of them but is not required.
*/

#include "Arduino.h";
#include "UdefDuePin.h"

#define E0_PWM X5  
#define FAN0_PWM X6 
#define BED_PWM X7 

void setup() {
}

void loop() {
  for (int i = 0 ; i<256 ;i++)
  { 
    analogWriteUndefined(FAN0_PWM, i);
    analogWriteUndefined(E0_PWM, i);
    analogWriteUndefined(BED_PWM, i);
    delay(10);
  }
  delay(500); 
  for (int i = 255 ; i>=0 ;i--)
  { 
    analogWriteUndefined(FAN0_PWM, i);
    analogWriteUndefined(E0_PWM, i);
    analogWriteUndefined(BED_PWM, i);
    delay(10);
  }
  delay(500);  
}
