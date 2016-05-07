///----------------------------------------------------------------------------------------
///
/// \file max17048.h
///
/// \brief 
///
/// \date 25.01.2016
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

#ifndef DRIVER_EXTERN_SENSORS_MAX17048_MAX17048_H_
#define DRIVER_EXTERN_SENSORS_MAX17048_MAX17048_H_

#include <stdint.h>

#define MAX17048_I2C_ADDR		0x36

#define MAX17048_REG_VCELL		0x02
#define MAX17048_REG_SOC		0x04
#define MAX17048_REG_MODE		0x06
#define MAX17048_REG_VERSION	0x08
#define MAX17048_REG_HIBRT		0x0A
#define MAX17048_REG_CONFIG		0x0C
#define MAX17048_REG_VALRT		0x14
#define MAX17048_REG_CRATE		0x16
#define MAX17048_REG_VRESET		0x18
#define MAX17048_REG_STATUS		0x1A
#define MAX17048_REG_CMD		0xFE

#define MAX17048_CMD_RESET		0x5400

enum MAX17048_MODE {
	MAX17048_QUICK_START = 0x4000,
	MAX17048_EN_SLEEP = 0x2000,
	MAX17048_HIB_STAT = 0x1000,
};

typedef struct {
	uint16_t athd:5;
	uint16_t alrt:1;
	uint16_t alsc:1;
	uint16_t sleep:1;
	//8bits
	uint16_t rcomp:8;
} MAX17048_CONFIG;

typedef struct {
	uint16_t vreset:7;
	uint16_t disable:1;
	//8bits
	uint16_t:8;
} MAX17048_VRESET;

typedef struct {
	uint16_t:1;
	uint16_t envr:1;
	uint16_t sc:1;
	uint16_t hd:1;
	uint16_t vr:1;
	uint16_t vl:1;
	uint16_t vh:1;
	uint16_t ri:1;
	//8bits
	uint16_t:8;
} MAX17048_STATUS;

uint16_t max17048_init();
uint16_t max17048_getVoltage();
uint16_t max17048_getCharge();
uint16_t max17048_readConfig();
uint16_t max17048_writeConfig(MAX17048_CONFIG config);
uint16_t max17048_getChargeRate();
uint16_t max17048_readStatus();
uint16_t max17048_writeStatus(MAX17048_STATUS status);
uint16_t max17048_sendCommand(uint16_t cmd);
uint16_t max17048_setMode(enum MAX17048_MODE mode);


#endif /* DRIVER_EXTERN_SENSORS_MAX17048_MAX17048_H_ */
