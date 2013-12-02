/*
  Read analog inputs on E0_temp and Bed_temp
  (investigate analogReadResolution() at some point)
 */
 
 //Analog input pins
uint8_t E0_temp = A4;
uint8_t Bed_temp = A5;
uint8_t E1_temp = A0;


void setup() {                
 SerialUSB.begin(115200);
 while (!SerialUSB) {}
 SerialUSB.println("Reading analog inputs");
}


void loop() {
  SerialUSB.print(" Bed_temp: ");
  SerialUSB.print(analogRead(Bed_temp));
  SerialUSB.print("E0_temp: ");
  SerialUSB.print(analogRead(E0_temp));
  SerialUSB.print("E1_temp: ");
  SerialUSB.print(analogRead(E1_temp));
  SerialUSB.println();
  delay(1000);
}
