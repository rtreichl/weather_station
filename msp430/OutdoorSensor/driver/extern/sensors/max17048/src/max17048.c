///----------------------------------------------------------------------------------------
///
/// \file max17048.c
///
/// \brief 
///
/// \date 26.01.2016
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

uint16_t max17048_init()
{
	MAX17048_CONFIG Config;
	Config.alsc = 0;
	Config.athd = 16;
	Config.alrt = 1;
	Config.sleep = 0;
	Config.rcomp = 0x97;
	max17048_writeConfig(Config);
	return 0;
}

uint16_t max17048_getVoltage()
{
	return betoh16(i2c_read_smbus_word(MAX17048_I2C_ADDR, MAX17048_REG_VCELL));
}

uint16_t max17048_getCharge()
{
	return betoh16(i2c_read_smbus_word(MAX17048_I2C_ADDR, MAX17048_REG_SOC));
}

uint16_t max17048_readConfig()
{
	return betoh16(i2c_read_smbus_word(MAX17048_I2C_ADDR, MAX17048_REG_CONFIG));
}

uint16_t max17048_writeConfig(MAX17048_CONFIG config)
{
	return i2c_write_smbus_word(MAX17048_I2C_ADDR, MAX17048_REG_CONFIG, htobe16(*((uint16_t *)&config)));
}

uint16_t max17048_getChargeRate()
{
	return betoh16(i2c_read_smbus_word(MAX17048_I2C_ADDR, MAX17048_REG_CRATE));
}

uint16_t max17048_readStatus()
{
	return betoh16(i2c_read_smbus_word(MAX17048_I2C_ADDR, MAX17048_REG_STATUS));
}

uint16_t max17048_writeStatus(MAX17048_STATUS status)
{
	return i2c_write_smbus_word(MAX17048_I2C_ADDR, MAX17048_REG_STATUS, htobe16(*((uint16_t *)&status)));
}

uint16_t max17048_sendCommand(uint16_t cmd)
{
	return i2c_write_smbus_word(MAX17048_I2C_ADDR, MAX17048_REG_CMD, htobe16(cmd));
}

uint16_t max17048_setMode(enum MAX17048_MODE mode)
{
	return i2c_write_smbus_word(MAX17048_I2C_ADDR, MAX17048_REG_MODE, htobe16(mode));
}
