///----------------------------------------------------------------------------------------
///
/// \file tmp102.c
///
/// \brief 
///
/// \date 31.12.2015
///
/// \author Richard Treichl
///
/// \remark
///
/// \todo
///
/// \version	1.0
///
///----------------------------------------------------------------------------------------

#include <driver.h>

uint16_t TMP102_init()
{
	TMP102_Config Config;
	//uint16_t *ptr_tmp = (uint16_t*) &Config;

	Config.OS = 0;
	Config.R = TMP102_RESOLUTION_12BIT;
	Config.F = TMP102_FAULT_QUEUE_6;
	Config.POL = TMP102_POLARITY_LOW;
	Config.TM = TMP102_INTERRUPT_MODE;
	Config.SD = TMP102_NORMAL_OPERATION;
	Config.CR = TMP102_CONVER_RATE_125MS;
	Config.AL = TMP102_ALERT_ZERO;
	Config.EM = TMP102_EXENDED_MODE;

	SwapEndian(&Config);

	i2c_write_smbus_word(TMP102_I2C_ADDR, TMP102_CONFIG_REG, *(uint16_t *)&Config);

	return 0;
}


int16_t TMP102_ReadTemperature()
{
	return (TMP102_ReadRawTemperature() * 625 * 2 / 100);
}

int16_t TMP102_ReadRawTemperature()
{
	int16_t temp = 0;

	SystemTimerDelay(SystemTimeDiff(200)); //Wait until system runing 125ms for conversion

	temp = i2c_read_smbus_word(TMP102_I2C_ADDR, TMP102_TEMPERATURE_REG);

	SwapEndian(&temp);

	if(temp & 0x0001) {
		temp >>= 3;
	}
	else {
		temp >>= 4;
	}

	return temp;
}
