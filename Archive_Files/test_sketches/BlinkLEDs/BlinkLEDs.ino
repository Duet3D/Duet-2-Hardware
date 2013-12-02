/*
  Cycle DUET and expansion board endstop pins from high to low to blink LEDS
 */

#define EXPANSION

 //LEDS on the DUET endstops
int ledE0 = 31;
int ledX = 11;
int ledY = 28;
int ledZ = 60;
#ifdef EXPANSION
int ledE1 = 24;
int ledE2 = 46;
int ledE3 = 45;
int ledE4 = 44;
#endif

void setup() {                
  pinMode(ledE0, OUTPUT);
  digitalWrite(ledE0, LOW);
  pinMode(ledX, OUTPUT);
  digitalWrite(ledX, LOW);
  pinMode(ledY, OUTPUT);
  digitalWrite(ledY, LOW);
  pinMode(ledZ, OUTPUT);
  digitalWrite(ledZ, LOW);
#ifdef EXPANSION  
  pinMode(ledE1, OUTPUT);
  digitalWrite(ledE1, LOW);
  pinMode(ledE2, OUTPUT);
  digitalWrite(ledE2, LOW);
  pinMode(ledE3, OUTPUT);
  digitalWrite(ledE4, LOW);
  pinMode(ledE4, OUTPUT);
  digitalWrite(ledE4, LOW);
#endif
}


void loop() {
  digitalWrite(ledE0, LOW);
  delay(75);
  digitalWrite(ledX, LOW);
  delay(30);
  digitalWrite(ledE0, HIGH);
  delay(75);
  digitalWrite(ledY, LOW);
  delay(30);
  digitalWrite(ledX, HIGH);
  delay(75);
  digitalWrite(ledZ, LOW);
  delay(30);
  digitalWrite(ledY, HIGH);
  delay(75);
#ifdef EXPANSION 
  digitalWrite(ledE1, LOW);
  delay(30);
#endif
  digitalWrite(ledZ, HIGH);
  delay(75);
#ifdef EXPANSION 
  digitalWrite(ledE2, LOW);
  delay(30); 
  digitalWrite(ledE1, HIGH);
  delay(75);
  digitalWrite(ledE3, LOW);
  delay(30); 
  digitalWrite(ledE2, HIGH);
  delay(75);
  digitalWrite(ledE4, LOW);
  delay(30); 
  digitalWrite(ledE3, HIGH);
  delay(75);  
  digitalWrite(ledE4, HIGH);
  delay(30);
#endif
}
