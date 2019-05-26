#include "MCP23x17.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

void CMCP23x17::pinMode(uint8_t pin, uint8_t mode)
{
  if (mode == INPUT)
    write_reg16(IODIR, read_reg16(IODIR) | 1<<pin);
  else
    write_reg16(IODIR, read_reg16(IODIR) & ~(1<<pin));
}

void CMCP23x17::digitalWrite(uint8_t pin, uint8_t val)
{
  if (val)
    write_reg16(GPIO, read_reg16(GPIO) | 1<<pin);
  else
    write_reg16(GPIO, read_reg16(GPIO) & ~(1<<pin));
}

int CMCP23x17::digitalRead(uint8_t pin)
{
  return (read_reg16(GPIO) & 1<<pin) != 0;
}

void CMCP23x17::pinMode16(uint16_t mode)
{
  write_reg16(IODIR, mode);
}

void CMCP23x17::digitalWrite16(uint16_t val)
{
  write_reg16(GPIO, val);
}

uint16_t CMCP23x17::digitalRead16()
{
  return read_reg16(GPIO);
}
