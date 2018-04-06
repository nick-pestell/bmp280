#include "Arduino.h"
#include "bmp280.h"
#include <SPI.h>

bmp280::bmp280(int slaveSelectPin){
	
	
	// set up chip select pin
	pinMode(slaveSelectPin, OUTPUT);

	_slaveSelectPin = slaveSelectPin;
	
}

void bmp280::initSPI(){
	
	// initialize SPI with parameters
	SPI.begin();
	
}

bool bmp280::connect(){

	if (readFrom(ID_REG,1) == 0x58){
		// diable temp
		byte osrs = readFrom(CTRL_MEAS_REG,1);
		byte reset_osrs = (osrs & 0xE3);
		writeTo(CTRL_MEAS_REG,reset_osrs);
		return true;}
		else{
		return false;}
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

  SPI.transfer(address); // send address
  SPI.transfer(value); // send value
  // de-select device
  digitalWrite(_slaveSelectPin, HIGH);
}

// get pressure 
byte bmp280::readPress(){
	
  // make address with reg and read bit
  byte address = (PRESS_REG1 | 0x80);
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  digitalWrite(_slaveSelectPin, LOW);

  SPI.transfer(address); // send address

  byte MS = SPI.transfer(0x00);
  MS = MS << 8;
  byte LS = SPI.transfer(0x00);
  byte result = MS | LS;
  digitalWrite(_slaveSelectPin, HIGH);
  return result;
}