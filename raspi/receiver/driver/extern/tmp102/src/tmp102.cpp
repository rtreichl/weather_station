#include <driver.h>
#include <iostream>
//#include <wiringPiI2C.h>
//#include <wiringPi.h>
#include <endian.h>
//#include <sys/ioctl.h>
//#include <linux/i2c-dev.h>

#define I2C_BUS 1

using namespace std;
using std::hex;

TMP102::TMP102(uint8_t i2c_device, uint8_t address, const TMP102_Config &config):I2C(i2c_device, address)
{
	//uint16_t read = 0;
//	if ((this->device = i2cOpen(I2C_BUS, Adr, 0)) < 0)
//	{
//		cout << "Error can't connect to 0x" << Adr << "!";
//	}
	
	if (*((uint16_t *)&config) == 0)
	{
		this->config.OS = 0;
		this->config.R = TMP102_RESOLUTION_12BIT;
		this->config.F = TMP102_FAULT_QUEUE_6;
		this->config.POL = TMP102_POLARITY_LOW;
		this->config.TM = TMP102_INTERRUPT_MODE;
		this->config.SD = TMP102_NORMAL_OPERATION;
		this->config.CR = TMP102_CONVER_RATE_1S;
		this->config.AL = TMP102_ALERT_ZERO;
		this->config.EM = TMP102_EXENDED_MODE;
		SetConfig(this->config);
	}
	else
	{
		SetConfig(config);
	}
}

int TMP102::GetConfig(TMP102_Config *config)
{
	config = &(this->config);
	return 0;
}

int TMP102::SetConfig(const TMP102_Config &config)
{
	
	uint16_t * send = 0;
	this->config = config;
	this->config.AL = TMP102_ALERT_ZERO;
	send = (uint16_t *)&(this->config);
	*send = htobe16(*send);
	
//	if (i2cWriteWordData(this->Device, TMP102_CONFIG_REG, *send) < 0)
//	{
//		if (i2cReadWordData(this->Device, TMP102_CONFIG_REG) != *send)
//		{
//			cout << "Error can't configure register 0x" << TMP102_CONFIG_REG << "with value 0x" << *send << "!";
//		}
//	}
	if (I2CSmBusWriteWord(TMP102_CONFIG_REG, *send) < 0)
		{
			if (I2CSmBusReadWord(TMP102_CONFIG_REG) != *send)
			{
				cout << "Error can't configure register 0x" << TMP102_CONFIG_REG << "with value 0x" << *send << "!";
			}
		}
	return 0;
}

float TMP102::ReadTemperature()
{
	union {
		uint8_t byte[2];
		int16_t word;
	} Receive;
	
	Receive.word = I2CSmBusReadWord(TMP102_TEMPERATURE_REG);
	//Receive.word = i2cReadWordData(this->Device, TMP102_TEMPERATURE_REG);
	Receive.word  = ((int8_t)Receive.byte[0] << 4) | ((uint8_t)Receive.byte[1] >> 4); 
	if (this->config.EM == TMP102_EXENDED_MODE)
		return Receive.word * 0.0625 * 2;
	else
		return Receive.word * 0.0625;
}

TMP102::~TMP102()
{
}
