#ifndef bmp280_h
#define bmp280_h

#include "Arduino.h"
#include <SPI.h>

// define registers
#define ID_REG 0xD0
#define RESET_REG 0xE0
#define STATUS_REG 0xF3
#define CTRL_MEAS_REG 0x03
#define CONFIG_REG 0xF5
#define PRESS_REG1 0xF7
#define PRESS_REG2 0xF8
#define PRESS_REG3 0xF9
#define TEMP_REG1 0XFA
#define TEMP_REG2 0XFB
#define TEMP_REG3 0XFC

class bmp280
{
  public:
    bmp280(int slaveSelectPin);
    void writeTo(byte reg, byte value);
    byte readFrom(byte reg, int byteNo);
	byte readPress();
	bool connect();
	void initSPI();
	
  private:
	int _slaveSelectPin;

};

#endif