///----------------------------------------------------------------------------------------
///
/// \file protocol2.c
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

#include <driver.h>
#include "../include/protocol.h"
#include <string.h>

#define RASPBERRY_PI_ADDR	0x01

uint16_t protocol_add_data(PROTOCOL_BUFFER_STC *buffer, uint8_t size, void *data)
{
	uint8_t *tmp_data = (uint8_t *)data;
	for(;size > 0; size--) {
		buffer->data[buffer->size] = *tmp_data;
		tmp_data++;
		buffer->size++;
	}
	buffer->size += size;
	return 0;
}

