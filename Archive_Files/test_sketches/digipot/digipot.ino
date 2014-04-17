/*
Test code for the MCP4461 on the DUET 0.3/0.4/0.5
Note that in version 0.3 of the board Channels 2 and 3 have GND connected to Pin
B and VDD connected to PinA while Channels 0 and 1 are reversed.

This was changed from version 0.4 onwards to have VDD on pin A and GND on pin B for all channels.

The expansion board 0.1 is on the same I2C bus with pin A1 high so its addres is 0X2E

*/
#include "Arduino.h"
#include <Wire.h>
#include "MCP4461.h"

#define EXPANSION  //if an expansion board is connected, do not define if not connected.

MCP4461 mcp_duet;

#ifdef EXPANSION
MCP4461 mcp_exp;
#endif

void setup()
{
  SerialUSB.begin(115200);
  while (!SerialUSB) {}
  SerialUSB.println("Initialising Library ");
  mcp_duet.begin(); //only call begin once in the entire execution, this begins the I2C comms on that channel for all objects
  #ifdef EXPANSION
  mcp_exp.setMCP4461Address(0x2E);
  #endif
}

void loop()
{
  //test the duet quad channel pot
  delay(1000);
  SerialUSB.print(" Reading Duet Status Register ");
  SerialUSB.println(mcp_duet.getStatus(),BIN);
  SerialUSB.println(" Setting Duet Volatile Wipers ");
  mcp_duet.setVolatileWiper(0,0x90); //for 0.4 onwards 0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)
  mcp_duet.setVolatileWiper(1,0x90); //for 0.4 onwards 0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)
  mcp_duet.setVolatileWiper(2,0x70); //0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)
  mcp_duet.setVolatileWiper(3,0x70); //0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)
  SerialUSB.println(" Setting Duet Non Volatile Wipers"); 
  mcp_duet.setNonVolatileWiper(0,0x90);
  mcp_duet.setNonVolatileWiper(1,0x90);
  mcp_duet.setNonVolatileWiper(2,0x70);
  mcp_duet.setNonVolatileWiper(3,0x70);
  SerialUSB.println(" Get each Duet Wiper value in turn ");
  for(int i = 0; i<4; i++)
  {
    SerialUSB.print(String("Duet Wiper ")+ i + String(" Volatile :0x"));
    SerialUSB.print(mcp_duet.getVolatileWiper(i),HEX);
    SerialUSB.print(" NonVolatile :0x");
    SerialUSB.println(mcp_duet.getNonVolatileWiper(i),HEX);  
  }
  #ifdef EXPANSION
  //repeat for the expansion board
  delay(1000);
  SerialUSB.print(" Reading Expansion Status Register ");
  SerialUSB.println(mcp_exp.getStatus(),BIN);
  SerialUSB.println(" Setting Expansion Volatile Wipers ");
  mcp_exp.setVolatileWiper(0,0x90); //0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)
  mcp_exp.setVolatileWiper(1,0x90); //0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)
  mcp_exp.setVolatileWiper(2,0x70); //0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)
  mcp_exp.setVolatileWiper(3,0x70); //0x0 = Vref Off, 0x100 = Vref High (~1,6V), 0x80 = Vref 50% (~0.8V)
  SerialUSB.println(" Setting Expansion Non Volatile Wipers"); 
  mcp_exp.setNonVolatileWiper(0,0x90);
  mcp_exp.setNonVolatileWiper(1,0x90);
  mcp_exp.setNonVolatileWiper(2,0x70);
  mcp_exp.setNonVolatileWiper(3,0x70);
  SerialUSB.println(" Get each Expansion Wiper value in turn ");
  for(int i = 0; i<4; i++)
  {
    SerialUSB.print(String("Expansion Wiper ")+ i + String(" Volatile :0x"));
    SerialUSB.print(mcp_exp.getVolatileWiper(i),HEX);
    SerialUSB.print(" NonVolatile :0x");
    SerialUSB.println(mcp_exp.getNonVolatileWiper(i),HEX);  
  }
  #endif
  delay(5000);
}

