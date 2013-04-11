/*
  Cycle DUET endstop pins from high to low to blink LEDS
 */
 
 //LEDS on the DUET endstops
int ledE = 31;
int ledX = 11;
int ledY = 28;
int ledZ = 60;


void setup() {                
  pinMode(ledE, OUTPUT);
  pinMode(ledX, OUTPUT);  
  pinMode(ledY, OUTPUT);  
  pinMode(ledZ, OUTPUT);  
}


void loop() {
  digitalWrite(ledE, HIGH);
  delay(75);
  digitalWrite(ledX, HIGH);
  delay(30);
  digitalWrite(ledE, LOW);
  delay(75);
  digitalWrite(ledY, HIGH);
  delay(30);
  digitalWrite(ledX, LOW);
  delay(75);
  digitalWrite(ledZ, HIGH);
  delay(30);
  digitalWrite(ledY, LOW);
  delay(75);
  digitalWrite(ledZ, LOW);
  delay(150);
}
