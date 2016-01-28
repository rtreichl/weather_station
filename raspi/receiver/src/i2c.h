#pragma once

#include <string>
#include <stdint.h>
using namespace std;

#define I2C_DEVICE_0	0
#define I2C_DEVICE_1	1

class I2C
{
public:
	I2C(uint8_t i2c_device, uint8_t addres);
	int I2CReadByte();
	int I2CReadWord();
	int I2CReadBlock(void *RxBuffer, uint8_t n_Bytes);
	int I2CWriteByte(uint8_t TxBuffer);
	int I2CWriteWord(uint16_t TxBuffer);
	int I2CWriteBlock(void *TxBuffer, uint8_t n_Bytes);
	int I2CSmBusReadByte(uint8_t reg);
	int I2CSmBusReadWord(uint8_t reg);
	int I2CSmBusReadBlock(uint8_t reg, void *RxBuffer);
	int I2CSmBusWriteByte(uint8_t reg, uint8_t TxBuffer);
	int I2CSmBusWriteWord(uint8_t reg, uint16_t TxBuffer);
	int I2CSmBusWriteBlock(uint8_t reg, void *TxBuffer, uint8_t n_Bytes);
	~I2C();
private:
	int device = 0;
	int address = 0;
};

