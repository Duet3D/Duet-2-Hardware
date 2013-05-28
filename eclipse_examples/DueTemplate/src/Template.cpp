/*
Template Arduino Due Eclipse project
*/

#include "Arduino.h"

void setup();
void loop();

int led = 31; //Duet LED on E Stop

void setup (void)
{
	Serial.begin(115200);
	Serial.println("Test Project");
	pinMode(led, OUTPUT);
}

void loop(void){
	digitalWrite(led, LOW);
	delay(300);
	digitalWrite(led, HIGH);
	delay(300);
}
