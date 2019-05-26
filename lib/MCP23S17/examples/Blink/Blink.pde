//This sample sets all pins of two MCP23S17 chips to 1, then to 0 repeatedly

//#include directive order is important!
//It should be SPI.h, MCP23x17.h, MCP23S17.h
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
