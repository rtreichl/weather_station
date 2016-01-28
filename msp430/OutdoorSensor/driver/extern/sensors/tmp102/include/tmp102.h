///----------------------------------------------------------------------------------------
///
/// \file tmp102.h
///
/// \brief 
///
/// \date 07.01.2016
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

#ifndef DRIVER_EXTERN_SENSORS_TMP102_INCLUDE_TMP102_H_
#define DRIVER_EXTERN_SENSORS_TMP102_INCLUDE_TMP102_H_

#define TMP102_TEMPERATURE_REG		0x00
#define TMP102_CONFIG_REG			0x01
#define TMP102_TEMP_LOW_REG			0x02
#define TMP102_TEMP_HIGH_REG		0x03
#define TMP102_MANF_ID_REG			0xFE
#define TMP102_DEV_ID_REG			0xFF
#define TMP102_SHUTDOWN				1
#define TMP102_NORMAL_OPERATION		0
#define TMP102_COMPERATOR_MODE		1
#define TMP102_INTERRUPT_MODE		0
#define TMP102_POLARITY_HIGH		1
#define TMP102_POLARITY_LOW			0
#define TMP102_FAULT_QUEUE_1		0
#define TMP102_FAULT_QUEUE_2		1
#define TMP102_FAULT_QUEUE_4		2
#define TMP102_FAULT_QUEUE_6		3
#define TMP102_RESOLUTION_12BIT		3
#define TMP102_ONE_SHOT				1
#define TMP102_NORMAL_MODE			0
#define TMP102_EXENDED_MODE			1
#define TMP102_ALERT_ZERO			0
#define TMP102_ALERT_ONE			1
#define TMP102_CONVER_RATE_4S		0
#define TMP102_CONVER_RATE_1S		1
#define TMP102_CONVER_RATE_250MS	2
#define TMP102_CONVER_RATE_125MS	3

typedef struct
{
	uint16_t _res1 : 4;
	uint16_t EM : 1;
	uint16_t AL : 1;
	uint16_t CR : 2;
	uint16_t SD : 1;
	uint16_t TM : 1;
	uint16_t POL: 1;
	uint16_t F : 2;
	uint16_t R : 2;
	uint16_t OS : 1;
}TMP102_Config;

#endif /* DRIVER_EXTERN_SENSORS_TMP102_INCLUDE_TMP102_H_ */
