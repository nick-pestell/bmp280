#include "Arduino.h"
#include "bmp280.h"
#include <SPI.h>

bmp280::bmp280(int slaveSelectPin){
	
	
	// set up chip select pin
	digitalWrite(slaveSelectPin, HIGH);
    pinMode(slaveSelectPin, OUTPUT);

	_slaveSelectPin = slaveSelectPin;
	
}

void bmp280::initSPI(){
	
	// initialize SPI with parameters
	SPI.begin();
	
}

bool bmp280::connect(){

	if (readFrom(ID_REG,1) != 0x58){
		return false;}
	// disable temp
	writeTo(CTRL_MEAS_REG,0x7);
	return true;

}
	

byte bmp280::readFrom(byte reg, int byteNo){

  // make address with reg and read bit
  byte address = (reg | 0x80);
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  digitalWrite(_slaveSelectPin, LOW);

  SPI.transfer(address); // send address

  // recieve first byte
  byte result = SPI.transfer(0x00);
  
  // recieve remaining bytes and form single number
  byteNo--;
  if (byteNo > 0){
    result = result << 8; // shift to the left one byte
    delayMicroseconds(30);
    byte inByte = SPI.transfer(0x00); // recieve next byte
    result = result | inByte;
    byteNo--;     
  }
  // de-select
  digitalWrite(_slaveSelectPin, HIGH);
  
  // return result
  return result;
}


void bmp280::writeTo(byte reg, byte value){

  // make address with reg and write bit
  byte address = (reg | 0x00);
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  digitalWrite(_slaveSelectPin, LOW);

  SPI.transfer(address & ~0x80); // send address
  SPI.transfer(value); // send value
  // de-select device
  digitalWrite(_slaveSelectPin, HIGH);
  SPI.endTransaction();
}

// get pressure 
uint16_t bmp280::readPress(){
	
  // make address with reg and read bit
  byte address = (PRESS_REG1 | 0x80);
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  digitalWrite(_slaveSelectPin, LOW);

  SPI.transfer(address); // send address

  uint16_t MS = SPI.transfer(0x00);
  MS = MS << 8;
  byte LS = SPI.transfer(0x00);
  uint16_t result = MS | LS;
  digitalWrite(_slaveSelectPin, HIGH);
  SPI.endTransaction();
  return result;
}

/*// read coeffecients
void bmp280::readCoefficients(){

    _bmp280_calib.dig_T1 = readFrom(BMP280_REGISTER_DIG_T1,2);
    _bmp280_calib.dig_T2 = readFrom(BMP280_REGISTER_DIG_T2,2);
    _bmp280_calib.dig_T3 = readFrom(BMP280_REGISTER_DIG_T3,2);

    _bmp280_calib.dig_P1 = readFrom(BMP280_REGISTER_DIG_P1,2);
    _bmp280_calib.dig_P2 = readFrom(BMP280_REGISTER_DIG_P2,2);
    _bmp280_calib.dig_P3 = readFrom(BMP280_REGISTER_DIG_P3,2);
    _bmp280_calib.dig_P4 = readFrom(BMP280_REGISTER_DIG_P4,2);
    _bmp280_calib.dig_P5 = readFrom(BMP280_REGISTER_DIG_P5,2);
    _bmp280_calib.dig_P6 = readFrom(BMP280_REGISTER_DIG_P6,2);
    _bmp280_calib.dig_P7 = readFrom(BMP280_REGISTER_DIG_P7,2);
    _bmp280_calib.dig_P8 = readFrom(BMP280_REGISTER_DIG_P8,2);
    _bmp280_calib.dig_P9 = readFrom(BMP280_REGISTER_DIG_P9,2);
}*/