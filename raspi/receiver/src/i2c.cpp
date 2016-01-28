#include "i2c.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
//#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <iostream>
//#include <linux/types.h>


using namespace std;

I2C::I2C(uint8_t i2c_device, uint8_t address)
{
	this->address = address;
	string dev;

	if (i2c_device == 0)
		dev = "/dev/i2c-0";
	else
		dev = "/dev/i2c-1";

	if ((this->device = open(dev.c_str(), O_RDWR)) < 0) {
		system("/sbin/modprobe i2c_dev");
		system("/sbin/modprobe i2c_bcm2708");
		if ((this->device = open(dev.c_str(), O_RDWR)) < 0) {
			cerr << "Failed to open '" << dev << "'" << endl;
			exit(-1);
		}
	}

	if (ioctl(this->device, I2C_SLAVE, this->address) < 0) {
		cerr << "Failed to find slave on address: 0x" << hex << address << endl;
		exit(-1);
	}
}



int I2C::I2CReadByte()
{
	uint8_t received = 0;
	read(this->device, &received, 1);
	return received;
}

int I2C::I2CReadWord()
{
	uint16_t received = 0;
	read(this->device, &received, 2);
	return received;
}

int I2C::I2CReadBlock(void *RxBuffer, uint8_t n_Bytes)
{
	return read(this->device, RxBuffer, n_Bytes);
}

int I2C::I2CWriteByte(uint8_t TxBuffer)
{
	return write(this->device, &TxBuffer, 1);
}

int I2C::I2CWriteWord(uint16_t TxBuffer)
{
	return write(this->device, &TxBuffer, 2);
	return 0;
}

int I2C::I2CWriteBlock(void *TxBuffer, uint8_t n_Bytes)
{
	return write(this->device, &TxBuffer, n_Bytes);
}

int I2C::I2CSmBusReadByte(uint8_t reg)
{
	return i2c_smbus_read_byte_data(this->device, reg);
}

int I2C::I2CSmBusReadWord(uint8_t reg)
{
	return i2c_smbus_read_word_data(this->device, reg);
}

int I2C::I2CSmBusReadBlock(uint8_t reg, void *RxBuffer)
{
	return i2c_smbus_read_block_data(this->device, reg, (uint8_t*)RxBuffer);;
}

int I2C::I2CSmBusWriteByte(uint8_t reg, uint8_t TxBuffer)
{
	return i2c_smbus_write_byte_data(this->device, reg, TxBuffer);
}

int I2C::I2CSmBusWriteWord(uint8_t reg, uint16_t TxBuffer)
{
	return i2c_smbus_write_word_data(this->device, reg, TxBuffer);;
}

int I2C::I2CSmBusWriteBlock(uint8_t reg, void *TxBuffer, uint8_t n_Bytes)
{
	return i2c_smbus_write_block_data(this->device, reg, n_Bytes, (uint8_t*)TxBuffer);;
}

I2C::~I2C()
{
	close(this->device);
}
