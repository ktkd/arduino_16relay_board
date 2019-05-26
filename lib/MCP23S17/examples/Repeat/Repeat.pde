//This sample reads pin state of 1'st MCP23S17 chip, and set the same values on 2'nd chip

//#include directive order is important!
//It should be SPI.h, MCP23x17.h, MCP23017.h
#include <SPI.h>
#include <MCP23x17.h>
#include <MCP23S17.h>

//Here we create two objects, but we cannot initialize them now, because SPI bus is not ready 
CMCP23S17 mcp23_1;
CMCP23S17 mcp23_2;

void setup()
{
  //Here we configure SPI bus
  SPI.begin();
  //and initialize MCP23* objects with CS pin 10 and addresses of 0 and 1
  mcp23_1.init(10, 0);
  mcp23_2.init(10, 1);

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
