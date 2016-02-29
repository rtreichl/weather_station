///----------------------------------------------------------------------------------------
///
/// \file protocol2.h
///
/// \brief 
///
/// \date 28.02.2016
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

#ifndef APP_INCLUDE_PROTOCOL2_H_
#define APP_INCLUDE_PROTOCOL2_H_

#include <stdint.h>

typedef enum {
	STATUS_OK,
	STATUS_LOW_ENERGY,
	STATUS_ERROR
} PROTOCOL_STATUS_E;

typedef enum {
	PROTOCOL_INFO,
	PROTOCOL_DATA,
} PROTOCOL_PROTOCOL_E;

typedef struct {
	uint8_t size;
	uint8_t data[40];
} PROTOCOL_BUFFER_STC;

typedef struct {
	uint16_t max17048:1;
	uint16_t si1147:1;
	uint16_t tmp102:1;
	uint16_t hdc1000:1;
	uint16_t lps25h:1;
	uint16_t ds18b20:1;
	uint16_t _res:10;
} PROTOCOL_HARDWARE_STC;

typedef struct {
	uint8_t length;
	uint8_t dest_addr:4;
	uint8_t src_addr:4;
	PROTOCOL_PROTOCOL_E protocol:4;
	PROTOCOL_STATUS_E status:4;
} PROTOCOL_HEADER_STC;

typedef struct {
	PROTOCOL_HEADER_STC header;
	PROTOCOL_HARDWARE_STC hardware;
	PROTOCOL_BUFFER_STC buffer;
} PROTOCOL_DATA_STC;

typedef struct {
	PROTOCOL_HEADER_STC header;
	PROTOCOL_HARDWARE_STC hardware;
	PROTOCOL_BUFFER_STC buffer;
} PROTOCOL_INFO_STC;

uint16_t protocol_add_data(PROTOCOL_BUFFER_STC *buffer, uint8_t size, void *data);

#endif /* APP_INCLUDE_PROTOCOL2_H_ */
