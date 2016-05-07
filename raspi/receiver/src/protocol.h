///----------------------------------------------------------------------------------------
///
/// \file protocol.h
///
/// \brief 
///
/// \date 03.01.2016
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

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <stdint.h>
#include "database.h"

typedef enum {
	STATUS_OK,
	STATUS_LOW_ENERGY,
	STATUS_ERROR
} PROTOCOL_STATUS_E;

typedef enum {
	PROTOCOL_INFO,
	PROTOCOL_DATA,
} PROTOCOL_PROTOCOL_E;

typedef struct __attribute__((__packed__)){
	uint8_t size;
	uint8_t data[40];
} PROTOCOL_BUFFER_STC;

typedef struct __attribute__((__packed__)){
	uint16_t max17048:1;
	uint16_t si1147:1;
	uint16_t tmp102:1;
	uint16_t hdc1000:1;
	uint16_t lps25h:1;
	uint16_t ds18b20:1;
	uint16_t solar:1;
	uint16_t _res:9;
	//uint8_t _res2:8;
} PROTOCOL_HARDWARE_STC;

typedef struct __attribute__((__packed__)){
	uint8_t length;
	uint8_t dest_addr:4;
	uint8_t src_addr:4;
	PROTOCOL_PROTOCOL_E protocol:4;
	PROTOCOL_STATUS_E status:4;
} PROTOCOL_HEADER_STC;

typedef struct __attribute__((__packed__)) {
	PROTOCOL_HEADER_STC header;
	PROTOCOL_HARDWARE_STC hardware;
	PROTOCOL_BUFFER_STC buffer;
} PROTOCOL_DATA_STC;

typedef struct __attribute__((__packed__)){
	PROTOCOL_HEADER_STC header;
	PROTOCOL_HARDWARE_STC hardware;
	PROTOCOL_BUFFER_STC buffer;
} PROTOCOL_INFO_STC;

#define HDC1000_TEMP_FACTOR			1.0 / 65535.0 * 165.0 - 40.0
#define HDC1000_HUMI_FACTOR			1.0 / 65535.0 * 100.0
#define TMP102_TEMP_FACTOR			0.0625
#define LPS25H_TEMP_FACTOR			1.0 / 480.0 + 42.5
#define LPS25H_PRESS_FACTOR			1.0 / 4096.0
#define SI1147_IR_FACTOR			1.0 / 2.44
#define SI1147_VIS_FACTOR			1.0 / 0.282
#define SI1147_UV_FACTOR			1.0 / 100.0
#define MAX17048_VCELL_FACTOR		78.125 / 1000000.0
#define MAX17048_CHARGE_FACTOR		1.0 / 256.0
#define MAX17048_CRATE_FACTOR		0.208
#define SOLAR_VOLT_FACTOR			1.5 / 1024.0
#define DS18B20_TEMP_FACTOR			0.125



int protocol_decoder(PROTOCOL_DATA_STC *protocol, DATABASE_DATA_STC *data);
int32_t protocol_print_data(DATABASE_DATA_STC *data);

#endif /* PROTOCOL_H_ */
