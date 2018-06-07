#ifndef bmp280_h
#define bmp280_h

#include "Arduino.h"
#include <SPI.h>

// define registers
#define ID_REG 0xD0
#define RESET_REG 0xE0
#define STATUS_REG 0xF3
#define CTRL_MEAS_REG 0xF4
#define CONFIG_REG 0xF5
#define PRESS_REG1 0xF7
#define PRESS_REG2 0xF8
#define PRESS_REG3 0xF9
#define TEMP_REG1 0xFA
#define TEMP_REG2 0xFB
#define TEMP_REG3 0xFC

/*typedef struct
    {
      uint16_t dig_T1;
      int16_t  dig_T2;
      int16_t  dig_T3;

      uint16_t dig_P1;
      int16_t  dig_P2;
      int16_t  dig_P3;
      int16_t  dig_P4;
      int16_t  dig_P5;
      int16_t  dig_P6;
      int16_t  dig_P7;
      int16_t  dig_P8;
      int16_t  dig_P9;

      uint8_t  dig_H1;
      int16_t  dig_H2;
      uint8_t  dig_H3;
      int16_t  dig_H4;
      int16_t  dig_H5;
      int8_t   dig_H6;
    } bmp280_calib_data;
*/
class bmp280
{
  public:
    bmp280(int slaveSelectPin);
    void writeTo(byte reg, byte value);
    byte readFrom(byte reg, int byteNo);
	uint16_t readPress();
	bool connect();
	void initSPI();
	void readCoefficients();
	
  private:
	int _slaveSelectPin;
	//bmp280_calib_data _bmp280_calib;

};

#endif