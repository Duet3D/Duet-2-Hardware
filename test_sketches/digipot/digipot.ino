/*
Test code for the MCP4461 on the DUET 0.3
Note that in this version of the board Channels 2 and 3 have GND connected to Pin
B and VDD connected to PinA while Channels 0 and 1 are reversed.
*/
#include "Arduino.h"
#include <Wire.h>
#include "MCP4461.h"

MCP4461 mcp;

void setup()
{
  SerialUSB.begin(115200);
  while (!SerialUSB) {}
  SerialUSB.println("Initialising Library ");
  mcp.begin();
}

void loop()
{
  delay(1000);
  SerialUSB.print(" Reading Status Register ");
  SerialUSB.println(mcp.getStatus(),BIN);
  SerialUSB.println(" Setting Volatile Wipers ");
  mcp.setVolatileWiper(0,0x90); //0x0 = Vref High (~1,6V), 0x100 = Vref Off, 0x80 = Vref 50% (~0.8V)
  mcp.setVolatileWiper(1,0x90); //0x0 = Vref High (~1,6V), 0x100 = Vref Off, 0x80 = Vref 50% (~0.8V)
  mcp.setVolatileWiper(2,0x70); //0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)
  mcp.setVolatileWiper(3,0x70); //0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)
  SerialUSB.println(" Setting Non Volatile Wipers"); 
  mcp.setNonVolatileWiper(0,0x90);
  mcp.setNonVolatileWiper(1,0x90);
  mcp.setNonVolatileWiper(2,0x70);
  mcp.setNonVolatileWiper(3,0x70);
  SerialUSB.println(" Get each Wiper value in turn ");
  for(int i = 0; i<4; i++)
  {
    SerialUSB.print(String("Wiper ")+ i + String(" Volatile :0x"));
    SerialUSB.print(mcp.getVolatileWiper(i),HEX);
    SerialUSB.print(" NonVolatile :0x");
    SerialUSB.println(mcp.getNonVolatileWiper(i),HEX);  
  }
  
  delay(5000);
}

