///----------------------------------------------------------------------------------------
///
/// \file lps25h.c
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

uint16_t LPS25H_init()
{
	i2c_write_smbus_byte(LPS25H_I2C_ADDR, LPS25H_CTRL1_REG, 0);

	i2c_write_smbus_byte(LPS25H_I2C_ADDR, LPS25H_CTRL2_REG, 0x40);

	i2c_write_smbus_byte(LPS25H_I2C_ADDR, LPS25H_RES_CONF_REG, 0);

	i2c_write_smbus_byte(LPS25H_I2C_ADDR, LPS25H_FIFO_CTRL_REG, 0xC0);

	i2c_write_smbus_byte(LPS25H_I2C_ADDR, LPS25H_CTRL1_REG, 0x94);

	return 0;

}

int16_t LPS25H_ReadRawTemperature()
{
	int16_t temp = 0;

	temp = i2c_read_smbus_word(LPS25H_I2C_ADDR, LPS25H_INCREMENT_REG(LPS25H_TEMP_OUT_L_REG));

	return temp;
}

int16_t LPS25H_ReadTemperature()
{
	return ((int32_t)LPS25H_ReadRawTemperature() * 10) / 48 + 4250;
}

uint32_t LPS25H_ReadRawPressure()
{
	uint32_t press = 0;
	I2C_SMBUS_PACKAGE smbus;

	smbus.reg = LPS25H_INCREMENT_REG(LPS25H_PRESS_OUT_XL_REG);
	smbus.data = &press;
	smbus.n_bytes = 3;

	i2c_read_smbus_block(LPS25H_I2C_ADDR, &smbus);
	return press;
}

uint32_t LPS25H_ReadPressure()
{
	uint32_t press = LPS25H_ReadRawPressure();
	press = press * 100;
	press = press >> 12;

	return press;
}
