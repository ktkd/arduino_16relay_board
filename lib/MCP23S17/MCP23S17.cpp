#include "MCP23S17.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "SPI.h"

CMCP23S17::CMCP23S17()
{
}

CMCP23S17::CMCP23S17(uint8_t ss_pin, uint8_t hw_addr, bool reinit_HAEN)
{
	init(ss_pin, hw_addr, reinit_HAEN);
}

void CMCP23S17::init(uint8_t ss_pin, uint8_t hw_addr, bool reinit_HAEN)
{
  m_ss_pin = ss_pin;
  ::digitalWrite(ss_pin, HIGH);
  ::pinMode(ss_pin, OUTPUT);

  m_write_cmd = 0x40;
  m_read_cmd = 0x41;
  if (reinit_HAEN) {
    write_reg16(IOCON, HAEN | (HAEN << 8));
  }
  m_write_cmd |= hw_addr << 1;
  m_read_cmd |= hw_addr << 1;
}

void CMCP23S17::write_reg16(uint8_t addr, uint16_t data)
{
  ::digitalWrite(m_ss_pin, LOW);
  SPI.transfer(m_write_cmd);
  SPI.transfer(addr);
  SPI.transfer(low_byte(data));
  SPI.transfer(high_byte(data));
  ::digitalWrite(m_ss_pin, HIGH);
}

uint16_t CMCP23S17::read_reg16(uint8_t addr)
{
  uint8_t lbyte, hbyte;
  ::digitalWrite(m_ss_pin, LOW);
  SPI.transfer(m_read_cmd);
  SPI.transfer(addr);
  lbyte = SPI.transfer(0);
  hbyte = SPI.transfer(0);
  ::digitalWrite(m_ss_pin, HIGH);
  return make_uint16(lbyte, hbyte);
}
