///----------------------------------------------------------------------------------------
///
/// \file device.c
///
/// \brief 
///
/// \date 26.02.2016
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
#include <library.h>
#include "../include/protocol.h"

uint16_t DeviceGetAddress()
{
	uint16_t addr = 0;

	// Config pins as input
	GPIO8_DIR(GPIO8_PORT3) &= ~GPIO_PIN2 + GPIO_PIN3;
	GPIO8_DIR(GPIO8_PORT1) &= ~GPIO_PIN3;

	// Enable pullups of pins
	GPIO8_REN(GPIO8_PORT3) |= GPIO_PIN2 + GPIO_PIN3;
	GPIO8_OUT(GPIO8_PORT3) |= GPIO_PIN2 + GPIO_PIN3;
	GPIO8_REN(GPIO8_PORT1) |= GPIO_PIN3;
	GPIO8_OUT(GPIO8_PORT1) |= GPIO_PIN3;

	if(!(GPIO8_IN(GPIO8_PORT3) & GPIO_PIN2)) {
		addr += 4;
	}

	if(!(GPIO8_IN(GPIO8_PORT3) & GPIO_PIN3)) {
		addr += 2;
	}

	if(!(GPIO8_IN(GPIO8_PORT1) & GPIO_PIN3)) {
		addr += 1;
	}

	return addr;
}

uint16_t DeviceGetExternalHardware()
{
	uint16_t config = 0;

	// Config pins as input
	GPIO8_DIR(PJ_BASE) &= ~GPIO_PIN0 + GPIO_PIN1;

	// Enable pullups of pins
	GPIO8_REN(PJ_BASE) |= GPIO_PIN0 + GPIO_PIN1;
	GPIO8_OUT(PJ_BASE) |= GPIO_PIN0 + GPIO_PIN1;

	if(!(GPIO8_IN(PJ_BASE) & GPIO_PIN1)) {
		config += 2;
	}

	if(!(GPIO8_IN(PJ_BASE) & GPIO_PIN0)) {
		config += 1;
	}

	return config;
}

uint16_t DeviceInitExternalHardware(PROTOCOL_HARDWARE_STC *hw)
{
	uint16_t config = DeviceGetExternalHardware();

	switch (config) {
	case 1:
		onewire_init(GPIO8_PORT1, GPIO_PIN0);
		if (onewire_reset()) {
			ds18b20_init(GPIO8_PORT1, GPIO_PIN0);
			ds18b20_StartConversion();
			hw->ds18b20 = 1;
		}
		break;
	case 2:
		if (i2c_slave_check(SI1147_I2C_ADDR)) {
			si1147_init();
			hw->si1147 = 1;
		}
		break;

	}
	return *(uint16_t *) hw;
}

uint16_t DeviceInitInternalHardware(PROTOCOL_HARDWARE_STC *hw)
{
	adc_init();
	hw->solar = 1;
	i2c_slave_check(HDC1000_I2C_ADDR);
	if(i2c_slave_check(HDC1000_I2C_ADDR)) {
		HDC1000_init();
		hw->hdc1000 = 1;
	}
	SystemTimerDelay(1);
	if(i2c_slave_check(TMP102_I2C_ADDR)) {
		TMP102_init();
		hw->tmp102 = 1;
	}
	SystemTimerDelay(1);
	if(i2c_slave_check(LPS25H_I2C_ADDR)) {
		LPS25H_init();
		hw->lps25h = 1;
	}
	SystemTimerDelay(1);
	if(i2c_slave_check(MAX17048_I2C_ADDR)) {
		max17048_init();
		hw->max17048 = 1;
	}
	return *(uint16_t *)hw;
}

uint16_t DeviceTurnOffinMs(uint16_t ms)
{
	while(GPIO8_IN(GPIO8_PORT2) & GPIO_PIN5); //Wait for package sent
	SystemTimerDelay(ms);
	while(1) {
		GPIO8_OUT(GPIO8_PORT3) |= GPIO_PIN7;
		SystemTimerDelay(10);
		GPIO8_OUT(GPIO8_PORT3) &= ~GPIO_PIN7;
	}
}
