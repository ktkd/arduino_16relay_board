//This sample sets all pins of two MCP23017 chips to 1, then to 0 repeatedly

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

  //We can configure all pins as outputs in a loop   
  for (int i=0; i<16; i++) {
    mcp23_1.pinMode(i, OUTPUT);
    mcp23_2.pinMode(i, OUTPUT);
  }
  //or, we can configure all 16 pins at once, calling pinMode16 method
  //mcp23_1.pinMode16(0x00000);
  //mcp23_2.pinMode16(0x00000);
}

void loop()
{
  //We can switch all pins to HIGH with a loop
  for (int i=0; i<16; i++) {
    mcp23_1.digitalWrite(i, HIGH);
    mcp23_2.digitalWrite(i, HIGH);
  }
  //or, we can swith all pins at once with digitalWrite16 method 
  //mcp23_1.digitalWrite16(0x0ffff);
  //mcp23_2.digitalWrite16(0x0ffff);
  delay(500);
  //...same for LOW
  for (int i=0; i<16; i++) {
    mcp23_1.digitalWrite(i, LOW);
    mcp23_2.digitalWrite(i, LOW);
  }
  //mcp23_1.digitalWrite16(0x00000);
  //mcp23_2.digitalWrite16(0x00000);
  delay(500);
}
