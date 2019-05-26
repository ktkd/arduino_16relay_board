#include "MCP23017.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Wire.h"

#if defined(ARDUINO) && ARDUINO >= 100
#define WIRE_WRITE(x) Wire.write(x)
#define WIRE_READ() Wire.read()
#else
#define WIRE_WRITE(x) Wire.send(x)
#define WIRE_READ() Wire.receive()
#endif

CMCP23017::CMCP23017()
{
}

CMCP23017::CMCP23017(uint8_t hw_addr)
{
	init(hw_addr);
}

void CMCP23017::init(uint8_t hw_addr)
{
  m_write_cmd = m_read_cmd = 0x20 | hw_addr;
}

void CMCP23017::write_reg16(uint8_t addr, uint16_t data)
{
  Wire.beginTransmission(m_write_cmd);
  WIRE_WRITE(addr);
  WIRE_WRITE(low_byte(data));
  WIRE_WRITE(high_byte(data));
  Wire.endTransmission();
}

uint16_t CMCP23017::read_reg16(uint8_t addr)
{
  uint8_t lbyte, hbyte;
  Wire.beginTransmission(m_write_cmd);
  WIRE_WRITE(addr);
  Wire.endTransmission();
  Wire.requestFrom(m_read_cmd, (uint8_t)2);
  while (Wire.available() < 2);
  lbyte = WIRE_READ();
  hbyte = WIRE_READ();
  return make_uint16(lbyte, hbyte);
}
