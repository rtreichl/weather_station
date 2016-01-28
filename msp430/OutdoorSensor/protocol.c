///----------------------------------------------------------------------------------------
///
/// \file protocol.c
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

#include <driver.h>
#include "protocol.h"

#ifndef PROTOCOL_C_
#define PROTOCOL_C_

#define RASPBERRY_PI_ADDR	0x01

int16_t protocol_static_data_collector(PROTOCOL_STC *protocol);
int16_t protocol_1_data_collector();
int16_t protocol_2_data_collector();
int16_t protocol_3_data_collector();
int16_t protocol_4_data_collector();

int16_t protocol_send()
{
	PROTOCOL_STC protocol;

	//protocol.command = CC110L_TXFIFO + CC110L_BURST;
	protocol.header.dest_addr = RASPBERRY_PI_ADDR;
	protocol.header.src_addr = protocol_get_addr();
	protocol.header.status = 0;

	protocol.static_data.solar_voltage = adc_getResult();
	protocol.static_data.max17048_vcell = max17048_getVoltage();
	protocol.static_data.max17048_charge = max17048_getCharge();
	protocol.static_data.max17048_crate = max17048_getChargeRate();
	protocol.static_data.hdc1000_temp = HDC1000_ReadRawTemperature();
	protocol.static_data.hdc1000_humi = HDC1000_ReadRawHumidity();
	protocol.static_data.tmp102_temp = TMP102_ReadRawTemperature();

	protocol.header.length = sizeof(PROTOCOL_STC) - PROTOCOL_DYNAMIC_BUFFER_SIZE - 2; ///> -2 cause length and command byte are not counted

	switch(protocol_get_protocol()) {
	case PROTOCOL_1:
	{
		PROTOCOL_PORT_1_DATA_STC *dynamic_data = (PROTOCOL_PORT_1_DATA_STC *)&protocol.dyn_data;
		dynamic_data->lps25h_temp = LPS25H_ReadRawTemperature();
		dynamic_data->lps25h_press = LPS25H_ReadRawPressure();
		si1147_single_conv();
		dynamic_data->si1147_ir = si1147_ReadRawIR();
		dynamic_data->si1147_vis = si1147_ReadRawVisible();
		dynamic_data->si1147_uv = si1147_ReadRawUV();
		protocol.header.length += sizeof(PROTOCOL_PORT_1_DATA_STC);
		protocol.header.protocol = PROTOCOL_1;
	}
		break;
	case PROTOCOL_2:
	{
		PROTOCOL_PORT_2_DATA_STC *dynamic_data = (PROTOCOL_PORT_2_DATA_STC *)&protocol.dyn_data;
		dynamic_data->lps25h_press = LPS25H_ReadRawPressure();
		dynamic_data->lps25h_temp = LPS25H_ReadRawTemperature();
		protocol.header.length += sizeof(PROTOCOL_PORT_2_DATA_STC);
		protocol.header.protocol = PROTOCOL_2;
	}
		break;
	case PROTOCOL_3:
	{
		PROTOCOL_PORT_3_DATA_STC *dynamic_data = (PROTOCOL_PORT_3_DATA_STC *)&protocol.dyn_data;
		si1147_single_conv();
		dynamic_data->si1147_ir = si1147_ReadRawIR();
		dynamic_data->si1147_vis = si1147_ReadRawVisible();
		dynamic_data->si1147_uv = si1147_ReadRawUV();
		protocol.header.length += sizeof(PROTOCOL_PORT_3_DATA_STC);
		protocol.header.protocol = PROTOCOL_3;
	}
		break;
	case PROTOCOL_4:
		protocol.header.length += sizeof(PROTOCOL_PORT_4_DATA_STC);
		protocol.header.protocol = PROTOCOL_4;
		break;
	default:
		return -1;
	}
	CC110L_SendCommand(CC110L_COMMAND_STX);
	CC110L_ReadStatus();
	CC110L_TX(&protocol, protocol.header.length + 2);
	return 0;
}

uint8_t protocol_get_addr()
{
	uint8_t addr = 0;
	//Config Port for addr 1, 2;
	P3DIR |= BIT2 + BIT3;
	P3REN |= BIT2 + BIT3;
	P3OUT |= BIT2 + BIT3;
	//Config Port for addr 0;
	P1DIR |= BIT3;
	P1REN |= BIT3;
	P1OUT |= BIT3;

	addr |=  (P3IN & BIT2) | ((P3IN & BIT3) >> 2) | ((P1IN & BIT3) >> 3);

	return addr;
}

uint8_t protocol_get_protocol()
{
	uint8_t device = 0;
	//Config Port for device 0, 1;
	PJDIR |= BIT0 + BIT1;
	PJREN |= BIT0 + BIT1;
	PJOUT |= BIT0 + BIT1;

	device = 3 - (PJIN & (BIT0 + BIT1));
	device += 1;
	return device;
}

#endif /* PROTOCOL_C_ */
