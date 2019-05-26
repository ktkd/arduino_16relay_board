#ifndef MCP23017_H_INCLUDED
#define MCP23017_H_INCLUDED

#include "MCP23x17.h"

class CMCP23017 : public CMCP23x17
{
  public:
  CMCP23017();
  CMCP23017(uint8_t hw_addr);

  void init(uint8_t hw_addr = 0);
  void write_reg16(uint8_t addr, uint16_t data);
  uint16_t read_reg16(uint8_t addr);
};

#endif
