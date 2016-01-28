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

int HDC1000::GetIdentity()
{
	cout << "Serial ID: 0x" << hex << this->SerialID << endl;
	cout << "Manufacturer ID: 0x" << hex << this->ManufacturerID << endl;
	cout << "Device ID: 0x" << hex << this->DeviceID << endl;
	return 0;
}

HDC1000::HDC1000(uint8_t i2c_device, uint8_t address, const HDC1000_Config &Config):I2C(i2c_device, address)//, GPIO(HDC1000_INTERRUPT_PIN)
{
	uint16_t read = 0;
//	if ((this->Device = i2cOpen(I2C_BUS, Adr, 0)) < 0)
//	{
//		cout << "Error can't connect to 0x" << Adr << "!";
//	}
	
	//Read ID's
	this->SerialID = 0;
	read = I2CSmBusReadWord(HDC1000_SERIAL_ID_3_REG);
	//read = i2cReadWordData(this->Device, HDC1000_SERIAL_ID_3_REG);
	this->SerialID = (uint64_t)be16toh(read);
	read = I2CSmBusReadWord(HDC1000_SERIAL_ID_2_REG);
	//read = i2cReadWordData(this->Device, HDC1000_SERIAL_ID_2_REG);
	this->SerialID += (uint64_t)be16toh(read) << 16;
	read = I2CSmBusReadWord(HDC1000_SERIAL_ID_1_REG);
	//read = i2cReadWordData(this->Device, HDC1000_SERIAL_ID_1_REG);
	this->SerialID += (uint64_t)be16toh(read) << 32;
	read = I2CSmBusReadWord(HDC1000_DEV_ID_REG);
	//read = i2cReadWordData(this->Device, HDC1000_DEV_ID_REG);
	this->DeviceID = be16toh(read);
	read = I2CSmBusReadWord(HDC1000_MANF_ID_REG);
	//read = i2cReadWordData(this->Device, HDC1000_MANF_ID_REG);
	this->ManufacturerID = be16toh(read);	
	
	if (*((uint16_t *)&Config) == 0)
	{
		this->Config.RST = HDC1000_NORMAL_OPERATION;	
		this->Config.HEAT = HDC1000_HEATER_OFF;
		this->Config.MODE = HDC1000_MODE_BOTH;
		this->Config.TRES = HDC1000_TEMP_RES_14_BIT;
		this->Config.HRES = HDC1000_HUMI_RES_14_BIT;
		SetConfig(this->Config);
	}
	else
	{
		SetConfig(Config);
	}

	//GPIODirection(GPIO_IN);
	//gpioP

	gpioSetMode(HDC1000_INTERRUPT_PIN, PI_INPUT);
	gpioSetPullUpDown(HDC1000_INTERRUPT_PIN, PI_PUD_UP);
	gpioSetISRFuncEx(HDC1000_INTERRUPT_PIN, FALLING_EDGE, 0, this->HDC1000_Interrupt, (void *)(this));
	this->Interrupt = 0;
	//gpioSetISRFunc(HDC1000_INTERRUPT_PIN, FALLING_EDGE, 0, ISR);
}

int HDC1000::GetConfig(HDC1000_Config *Config)
{
	Config = &(this->Config);
	return 0;
}

int HDC1000::SetConfig(const HDC1000_Config &Config)
{
	
	uint16_t * send = 0;
	this->Config = Config;
	this->Config.BTST = HDC1000_BAT_VOLT_HIGHER_2V8;
	send = (uint16_t *)&(this->Config);
	*send = htobe16(*send);
	
//	if (i2cWriteWordData(this->Device, HDC1000_CONFIG_REG, *send) < 0)
//	{
//		if (i2cReadWordData(this->Device, HDC1000_CONFIG_REG) != *send)
//		{
//			cout << "Error can't configure register 0x" << HDC1000_CONFIG_REG << "with value 0x" << *send << "!";
//		}
//	}
	if (I2CSmBusWriteWord(HDC1000_CONFIG_REG, *send) < 0)
	{
		if (I2CSmBusReadWord(HDC1000_CONFIG_REG) != *send)
		{
			cout << "Error can't configure register 0x" << HDC1000_CONFIG_REG << "with value 0x" << *send << "!";	
		}
	}
	return 0;
}

int HDC1000::SetHeater(bool status)
{
	if (status == HDC1000_HEATER_ON)
	{
		this->Config.HEAT = HDC1000_HEATER_ON;
	}
	else
	{
		this->Config.HEAT = HDC1000_HEATER_OFF;
	}
	SetConfig(this->Config);
	return 0;
}

bool HDC1000::GetHeater()
{
	uint16_t temp;
	HDC1000_Config * received;
	temp = be16toh(I2CSmBusReadWord(HDC1000_CONFIG_REG));
	//temp = be16toh(i2cReadWordData(this->Device, HDC1000_CONFIG_REG));
	received = (HDC1000_Config *)&temp;
	if (received->HEAT == HDC1000_HEATER_ON)
	{
		return HDC1000_HEATER_ON;
	}
	else
	{
		return HDC1000_HEATER_OFF;
	}
}

int16_t HDC1000::ReadRawTemperature()
{
	int16_t receive;
	this->Interrupt = 0;
	I2CWriteByte(HDC1000_TEMPERATURE_REG);
	//i2cWriteByte(this->Device, HDC1000_TEMPERATURE_REG);
	while (!this->Interrupt){}
	receive  = I2CReadWord();
	//i2cReadDevice(this->Device, (char *)&receive, 2);
	receive = be16toh(receive);
	return receive;
}

float HDC1000::ReadTemperature()
{
	return (ReadRawTemperature() / 65536.0) * 165.0 - 40.0;
}

float HDC1000::ReadTemperature(int16_t RawData)
{
	return (RawData / 65536.0) * 165.0 - 40.0;
}

uint16_t HDC1000::ReadRawHumidity()
{
	uint16_t receive;
	this->Interrupt = 0;
	I2CWriteByte(HDC1000_HUMIDITY_REG);
	//i2cWriteByte(this->Device, HDC1000_HUMIDITY_REG);
	while (!this->Interrupt) {}
	receive = I2CReadWord();
	//i2cReadDevice(this->Device, (char *)&receive, 2);
	receive = be16toh(receive);
	return receive;
}

float HDC1000::ReadHumidity()
{
	return (ReadRawHumidity() / 65536.0) * 100;
}

float HDC1000::ReadHumidity(uint16_t RawData)
{
	return (RawData / 65536.0) * 100;
}

HDC1000::~HDC1000()
{
}

void HDC1000::HDC1000_Interrupt(int gpio, int level, uint32_t tick, void  *userdata)
{
	HDC1000 *hdc1000 = (HDC1000 *)userdata;
	hdc1000->Interrupt = 1;
}
