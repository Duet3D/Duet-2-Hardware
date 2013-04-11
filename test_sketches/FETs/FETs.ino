/*
Test code for FET outputs on DUET 0.3
Note on 0.3 the FETS come on automatically (the driver fets invert
the logic)

Requires direct access to PWM functions on the SAM to get access to harware PWM.

*/
#define E0_PWM 40
#define FAN0_PWM 41
#define BED_PWM 53

void setup() {
 //SerialUSB.begin(115200);
 //while (!SerialUSB) {}
 pinMode(E0_PWM, OUTPUT);
 pinMode(FAN0_PWM, OUTPUT);
 pinMode(BED_PWM, OUTPUT);
 digitalWrite(E0_PWM, 0); //disable to begin
 digitalWrite(FAN0_PWM, 0);
 digitalWrite(BED_PWM, 0);
}

void loop() {

  digitalWrite(FAN0_PWM, 1); //on
  digitalWrite(E0_PWM, 1); //on
  digitalWrite(BED_PWM, 1); //on
  delay(2000);
  digitalWrite(FAN0_PWM, 0); //off
  digitalWrite(E0_PWM, 0); //off
  digitalWrite(BED_PWM, 0); //on
  delay(2000);
  
  //Analogue write does not work as these pins are not
  //arduino PWM pins (although they do support PWM natively)
  for (int i = 0 ; i<256 ;i++)
  { 
    analogWrite(FAN0_PWM, i);
    analogWrite(E0_PWM, i);
    analogWrite(BED_PWM, i);
    delay(50);
  }
  digitalWrite(FAN0_PWM, 0); //off
  digitalWrite(E0_PWM, 0); //off
  digitalWrite(BED_PWM, 0); //off
  delay(2000);  
}
