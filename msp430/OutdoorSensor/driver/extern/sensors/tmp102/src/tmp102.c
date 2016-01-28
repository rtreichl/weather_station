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
	uint16_t *ptr_tmp = (uint16_t*) &Config;

	Config.OS = 0;
	Config.R = TMP102_RESOLUTION_12BIT;
	Config.F = TMP102_FAULT_QUEUE_6;
	Config.POL = TMP102_POLARITY_LOW;
	Config.TM = TMP102_INTERRUPT_MODE;
	Config.SD = TMP102_NORMAL_OPERATION;
	Config.CR = TMP102_CONVER_RATE_1S;
	Config.AL = TMP102_ALERT_ZERO;
	Config.EM = TMP102_EXENDED_MODE;

	SwapEndian(&Config);

	i2c_write_smbus_word(TMP102_I2C_ADDR, TMP102_CONFIG_REG, *ptr_tmp);

	return 0;
}


int16_t TMP102_ReadTemperature()
{
	return (TMP102_ReadRawTemperature() * 625 * 2 / 100);
}

int16_t TMP102_ReadRawTemperature()
{
	union {
		uint8_t byte[2];
		int16_t word;
	} data;

	data.word = i2c_read_smbus_word(TMP102_I2C_ADDR, TMP102_TEMPERATURE_REG);

	data.word  = ((int8_t)data.byte[0] << 4) | ((uint8_t)data.byte[1] >> 4);

	return data.word;
}
