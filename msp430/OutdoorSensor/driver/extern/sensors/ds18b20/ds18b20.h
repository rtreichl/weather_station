///----------------------------------------------------------------------------------------
///
/// \file ds18b20.h
///
/// \brief 
///
/// \date 16.02.2016
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

#ifndef DRIVER_EXTERN_SENSORS_DS18B20_DS18B20_H_
#define DRIVER_EXTERN_SENSORS_DS18B20_DS18B20_H_

#define DS18B20_COMMAND_CONVERT			0x44
#define DS18B20_COMMAND_READ_PAD		0xBE
#define DS18B20_COMMAND_WRITE_PAD		0x4E
#define DS18B20_COMMAND_COPY_PAD		0x48
#define DS18B20_COMMAND_RECALL			0xB8
#define DS18B20_COMMAND_READ_POWER		0xB4
#define DS18B20_COMMAND_SEARCH_ROM		0xF0
#define DS18B20_COMMAND_READ_ROM		0x33
#define DS18B20_COMMAND_MATCH_ROM		0x55
#define DS18B20_COMMAND_SKIP_ROM		0xCC
#define DS18B20_COMMAND_ALARM_SEARCH	0xEC

int16_t ds18b20_ReadTemperature();
uint16_t ds18b20_StartConversion();
uint16_t ds18b20_init(GPIO8_PORT port, GPIO_PIN pin);

#endif /* DRIVER_EXTERN_SENSORS_DS18B20_DS18B20_H_ */
