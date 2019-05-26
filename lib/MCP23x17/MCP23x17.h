#ifndef MCP23X17_H_INCLUDED
#define MCP23X17_H_INCLUDED

#include <inttypes.h>

class CIOExpander
{
  public:
  virtual void pinMode(uint8_t pin, uint8_t mode);
  virtual void digitalWrite(uint8_t pin, uint8_t val);
  virtual int digitalRead(uint8_t pin);
};

class CMCP23x17 : public CIOExpander
{
  public:
  virtual void write_reg16(uint8_t addr, uint16_t data);
  virtual uint16_t read_reg16(uint8_t addr);
//  virtual void write_reg8(uint8_t addr, uint8_t data);
//  virtual uint8_t read_reg8(uint8_t addr);

  void pinMode(uint8_t pin, uint8_t mode);
  void digitalWrite(uint8_t pin, uint8_t val);
  int digitalRead(uint8_t pin);

  void pinMode16(uint16_t mode);
  void digitalWrite16(uint16_t val);
  uint16_t digitalRead16();

  uint8_t m_read_cmd;
  uint8_t m_write_cmd;

  const static uint8_t IODIR = 0x00;
  const static uint8_t GPIO  = 0x12;
  const static uint8_t IOCON = 0x0A;

  inline uint8_t  low_byte(uint16_t x) { return x & 0x00FF; }
  inline uint8_t  high_byte(uint16_t x) { return x >> 8; }
  inline uint16_t make_uint16(uint8_t lbyte, uint8_t hbyte) { return (uint16_t)hbyte<<8 | (uint16_t)lbyte; }
};

#endif
