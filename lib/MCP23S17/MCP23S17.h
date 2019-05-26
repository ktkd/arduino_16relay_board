#ifndef MCP23S17_H_INCLUDED
#define MCP23S17_H_INCLUDED

#include "MCP23x17.h"

class CMCP23S17 : public CMCP23x17
{
  public:
  CMCP23S17();
  CMCP23S17(uint8_t ss_pin, uint8_t hw_addr = 0, bool reinit_HAEN = true);

  void init(uint8_t ss_pin, uint8_t hw_addr = 0, bool reinit_HAEN = true);
  void write_reg16(uint8_t addr, uint16_t data);
  uint16_t read_reg16(uint8_t addr);

  uint8_t m_ss_pin;

  const static uint8_t HAEN = 0x08;
};

#endif
