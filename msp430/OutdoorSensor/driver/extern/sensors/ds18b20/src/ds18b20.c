///----------------------------------------------------------------------------------------
///
/// \file ds18b20.c
///
/// \brief 
///
/// \date 23.02.2016
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

static uint16_t ds18b20_time = 0;

uint16_t ds18b20_init(GPIO8_PORT port, GPIO_PIN pin)
{
	onewire_init(port, pin);
	return 0;
}

uint16_t ds18b20_StartConversion()
{
	onewire_reset();
	onewire_write_byte(DS18B20_COMMAND_SKIP_ROM);
	onewire_write_byte(DS18B20_COMMAND_CONVERT);
	onewire_line_high();
	ds18b20_time = SystemTimeGet() + 800;
	return 0;
}

int16_t ds18b20_ReadTemperature()
{
	uint16_t temperature = 0;
	SystemTimerDelay(SystemTimeDiff(ds18b20_time));
	onewire_reset();
	onewire_write_byte(DS18B20_COMMAND_SKIP_ROM);
	onewire_write_byte(DS18B20_COMMAND_READ_PAD);
	temperature =  onewire_read_byte();
	temperature +=  (onewire_read_byte() << 8);
	onewire_line_high();
	return temperature;
}
