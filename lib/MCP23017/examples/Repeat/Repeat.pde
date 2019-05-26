//This sample reads pin state of 1'st MCP23017 chip, and set the same values on 2'nd chip

//#include directive order is important!
//It should be Wire.h, MCP23x17.h, MCP23017.h
#include <Wire.h>
#include <MCP23x17.h>
#include <MCP23017.h>

//Here we create two objects, but we cannot initialize them now, because I2C bus is not ready 
CMCP23017 mcp23_1;
CMCP23017 mcp23_2;

void setup()
{
  //Here we configure I2C bus
  Wire.begin();
  //and initialize MCP23* objects with addresses of 0 and 1
  mcp23_1.init(0);
  mcp23_2.init(1);

  //We can configure all pins of 1'st chip as inputs,
  //and all pins of 2'nd chip as outputs in a loop   
  for (int i=0; i<16; i++) {
    mcp23_1.pinMode(i, INPUT);
    mcp23_2.pinMode(i, OUTPUT);
  }
  //or, we can configure all 16 pins at once, calling pinMode16 method
  //mcp23_1.pinMode16(0x0ffff);
  //mcp23_2.pinMode16(0x00000);
}

void loop()
{
  //We can read all pins of 1'st chip and write same values to 2'nd in a loop
  for (int i=0; i<16; i++) {
    mcp23_2.digitalWrite(i, mcp23_1.digitalRead(i));
  }
  //or, we can do it at once with digitalRead16 and digitalWrite16 methods 
  //mcp23_2.digitalWrite16(mcp23_1.digitalRead16());
}
