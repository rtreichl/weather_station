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

#define PROTOCOL_1	0x01
#define PROTOCOL_2	0x02
#define PROTOCOL_3	0x03
#define PROTOCOL_4	0x04

#define PROTOCOL_DYNAMIC_BUFFER_SIZE 16

#define HDC1000_TEMP_REG	0x01
#define HDC1000_HUMI_REG	0x02
#define TMP102_TEMP_REG		0x03
#define LPS25H_TEMP_REG		0x04
#define LPS25H_PRESS_REG	0x05
#define SI1147_UV_REG		0x06
#define SI1147_IR_REG		0x07
#define SI1147_VIS_REG		0x08

typedef struct {
	uint8_t length;
	uint8_t dest_addr;
	uint8_t src_addr;
	uint8_t protocol;
	uint8_t status;
} PROTOCOL_HEADER_STC;

typedef struct {
	uint16_t solar_voltage;
	uint16_t max17048_vcell;
	uint16_t max17048_charge;
	int16_t max17048_crate;
	int16_t hdc1000_temp;
	uint16_t hdc1000_humi;
	int16_t tmp102_temp;
} PROTOCOL_STATIC_DATA_STC;

#define PROTOCOL_STATIC_DATA_OFFSET (sizeof(PROTOCOL_HEADER_STC) + 1)
#define PROTOCOL_PRTOCOL_DATA_OFFSET (sizeof(PROTOCOL_HEADER_STC) + sizeof(PROTOCOL_STATIC_DATA_STC) + 1)

typedef struct {
	int16_t 	lps25h_temp;
	uint32_t	lps25h_press;
	uint16_t 	si1147_ir;
	uint16_t	si1147_vis;
	uint16_t	si1147_uv;
} PROTOCOL_PORT_1_DATA_STC;

typedef struct {
	uint16_t 	lps25h_temp;
	uint32_t 	lps25h_press;
} PROTOCOL_PORT_2_DATA_STC;

typedef struct {
	uint16_t 	si1147_ir;
	uint16_t	si1147_vis;
	uint16_t	si1147_uv;
} PROTOCOL_PORT_3_DATA_STC;

typedef struct {
} PROTOCOL_PORT_4_DATA_STC;

typedef struct {
	uint8_t command;
	PROTOCOL_HEADER_STC header;
	PROTOCOL_STATIC_DATA_STC static_data;
	uint8_t dyn_data[PROTOCOL_DYNAMIC_BUFFER_SIZE];
} PROTOCOL_STC;

int16_t protocol_send();
uint8_t protocol_get_addr();
uint8_t protocol_get_protocol();
void protocol_generate_header(void *buffer);

#endif /* PROTOCOL_H_ */
