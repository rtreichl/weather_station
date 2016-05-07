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

//TODO Im

#include <driver.h>

static uint16_t LPS25H_irq_handler(uint8_t pin);

void LPS25H_irq_enable();

volatile uint8_t LPS25H_Interrupt = 0;

uint16_t LPS25H_init()
{
	//Powerdown device
	i2c_write_smbus_byte(LPS25H_I2C_ADDR, LPS25H_CTRL1_REG, 0x00);

	//Software reset
	//i2c_write_smbus_byte(LPS25H_I2C_ADDR, LPS25H_CTRL2_REG, 0x40);

	//INT1 data signal see CTRL_REG4 active low/open drain
	//i2c_write_smbus_byte(LPS25H_I2C_ADDR, LPS25H_CTRL3_REG, 0xC0);

	//data ready on INT1
	//i2c_write_smbus_byte(LPS25H_I2C_ADDR, LPS25H_CTRL4_REG, 0x01);

	//i2c_write_smbus_byte(LPS25H_I2C_ADDR, LPS25H_INT_CFG_REG, LPS25H_INT_ACTIVE);

	//AVG of both over 16 Samples
	//i2c_write_smbus_byte(LPS25H_I2C_ADDR, LPS25H_RES_CONF_REG, 0x05);

	//FIFO bypass mode
	//i2c_write_smbus_byte(LPS25H_I2C_ADDR, LPS25H_FIFO_CTRL_REG, 0x00);

	//Powerup device oneshot mode
	i2c_write_smbus_byte(LPS25H_I2C_ADDR, LPS25H_CTRL1_REG, 0x84);

	LPS25H_irq_enable();

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

uint16_t LPS25H_OneShot()
{
	uint16_t time = 100;
	i2c_write_smbus_byte(LPS25H_I2C_ADDR , LPS25H_CTRL2_REG ,0x01);
	time += SystemTimeGet();
	while (!LPS25H_Interrupt) {
		LPS25H_Interrupt = i2c_read_smbus_byte(LPS25H_I2C_ADDR, LPS25H_CTRL2_REG) & 0x01;
		LPS25H_Interrupt ^= 0x01;
		SystemTimerDelay(1);
		if(SystemTimeDiff(time) < 0)
			LPS25H_Interrupt = 1;
	}
	return 0;
}

uint16_t LPS25H_irq_handler(uint8_t pin) {
	LPS25H_Interrupt = 1;
	return 0;
}

void LPS25H_irq_enable()
{
	GPIO8_DIR(LPS25H_IRQ_PORT) &= ~LPS25H_IRQ_PIN;
	GPIO8_REN(LPS25H_IRQ_PORT) |= LPS25H_IRQ_PIN;
	GPIO8_OUT(LPS25H_IRQ_PORT) |= LPS25H_IRQ_PIN;
	GPIO8_IES(LPS25H_IRQ_PORT) |= LPS25H_IRQ_PIN;
	GpioAttachISR(LPS25H_IRQ_PORT, LPS25H_IRQ_PIN, LPS25H_irq_handler);
	GpioEnableInterupt(LPS25H_IRQ_PORT, LPS25H_IRQ_PIN);


  return;
}
