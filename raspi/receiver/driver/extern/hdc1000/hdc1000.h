#include "../../driver.h"
#include <stdint.h>
#include <pigpio.h>

#ifndef _HDC1000_
#define _HDC1000_

#define HDC1000_TEMPERATURE_REG		0x00
#define HDC1000_HUMIDITY_REG		0x01
#define HDC1000_CONFIG_REG			0x02
#define HDC1000_SERIAL_ID_1_REG		0xFB
#define HDC1000_SERIAL_ID_2_REG		0xFC
#define HDC1000_SERIAL_ID_3_REG		0xFD
#define HDC1000_MANF_ID_REG			0xFE
#define HDC1000_DEV_ID_REG			0xFF
#define HDC1000_SOFTWARE_RESET		1
#define HDC1000_NORMAL_OPERATION	0
#define HDC1000_HEATER_ON			1
#define HDC1000_HEATER_OFF			0
#define HDC1000_MODE_BOTH			1
#define HDC1000_MODE_SEPARATED		0
#define HDC1000_BAT_VOLT_HIGHER_2V8	0
#define HDC1000_BAT_VOLT_LOWER_2V8	0
#define HDC1000_TEMP_RES_11_BIT		1
#define HDC1000_TEMP_RES_14_BIT		0
#define HDC1000_HUMI_RES_14_BIT		0
#define HDC1000_HUMI_RES_11_BIT		1
#define HDC1000_HUMI_RES_8_BIT		2

#define HDC1000_INTERRUPT_PIN		4

//void HDC1000_Interrupt(int gpio, int level, uint32_t tick, void  *userdata);
//void ISR(int pin, int level, uint32_t tick);

class HDC1000: private I2C//, private GPIO
{
public:
	typedef struct
	{
		uint16_t _res1 : 8;
		uint16_t HRES : 2;
		uint16_t TRES : 1;
		uint16_t BTST : 1;
		uint16_t MODE : 1;
		uint16_t HEAT : 1;
		uint16_t _res2 : 1;
		uint16_t RST : 1;
	}HDC1000_Config;
	HDC1000(uint8_t i2c_device, uint8_t address, const HDC1000_Config &Config = {0});
	~HDC1000();
	int GetIdentity();
	int GetConfig(HDC1000_Config *Config);
	int SetConfig(const HDC1000_Config &Config);

	bool GetHeater();
	int SetHeater(bool status);
	float ReadTemperature();
	static float ReadTemperature(int16_t RawData);
	float ReadHumidity();
	static float ReadHumidity(uint16_t RawData);
private:
	int Interrupt;
	uint64_t SerialID;
	uint16_t ManufacturerID;
	uint16_t DeviceID;
	HDC1000_Config Config = {0};
	uint16_t ReadRawHumidity();
	int16_t ReadRawTemperature();
	static void HDC1000_Interrupt(int gpio, int level, uint32_t tick, void  *userdata);
};

#endif
