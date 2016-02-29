///----------------------------------------------------------------------------------------
///
/// \file app.c
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

#include "../app.h"
#include "../include/protocol.h"
#include "../include/device.h"
#include "../driver/extern/communication/cc110l/include/cc110l_config2.h"

uint16_t application_main()
{
	PROTOCOL_DATA_STC data = {0};
	data.header.dest_addr = DeviceGetAddress();
	data.header.src_addr =  1;//Rapi address
	data.header.protocol = PROTOCOL_DATA;
	data.header.length = sizeof(PROTOCOL_HEADER_STC) + sizeof(PROTOCOL_HARDWARE_STC);
	application_init(&data.hardware);

	if(data.hardware.max17048) {
		uint16_t tmp;
		tmp = max17048_getCharge();
		protocol_add_data(&data.buffer, 2, &tmp);
		tmp = max17048_getChargeRate();
		protocol_add_data(&data.buffer, 2, &tmp);
		tmp = max17048_getVoltage();
		protocol_add_data(&data.buffer, 2, &tmp);
	}

	if(data.hardware.si1147) {
		uint16_t tmp;
		tmp = si1147_ReadRawIR();
		protocol_add_data(&data.buffer, 2, &tmp);
		tmp = si1147_ReadRawUV();
		protocol_add_data(&data.buffer, 2, &tmp);
		tmp = si1147_ReadRawVisible();
		protocol_add_data(&data.buffer, 2, &tmp);
	}

	if(data.hardware.hdc1000) {
		uint16_t tmp;
		tmp = HDC1000_ReadRawTemperature();
		protocol_add_data(&data.buffer, 2, &tmp);
		tmp = HDC1000_ReadRawHumidity();
		protocol_add_data(&data.buffer, 2, &tmp);
	}

	if(data.hardware.tmp102) {
		uint16_t tmp;
		tmp = TMP102_ReadRawTemperature();
		protocol_add_data(&data.buffer, 2, &tmp);
	}

	if(data.hardware.lps25h) {
		uint32_t tmp;
		tmp = LPS25H_ReadRawPressure();
		protocol_add_data(&data.buffer, 4, &tmp);
		tmp = LPS25H_ReadRawTemperature();
		protocol_add_data(&data.buffer, 2, &tmp);
	}

	if(data.hardware.ds18b20) {
		uint16_t tmp;
		tmp = ds18b20_ReadTemperature();
		protocol_add_data(&data.buffer, 2, &tmp);
	}

	data.header.length += data.buffer.size;

	CC110L_SendCommand(CC110L_COMMAND_STX);
	CC110L_TX(&data, data.header.length + 1); //Due to length byte is also transmitted to the CC110L

	DeviceTurnOffinMs(100);

	return 0;
}

uint16_t application_init(void *hw)
{
	GPIO8_OUT(GPIO8_PORT3) &= ~GPIO_PIN7;
	GPIO8_DIR(GPIO8_PORT3) |= GPIO_PIN7;

	i2c_init(1, 200);

	SPI_init(SPIMODE1);

	adc_init();

	DeviceInitExternalHardware(hw);
	DeviceInitInternalHardware(hw);

	CC110L_SendCommand(CC110L_COMMAND_SRES);
	SystemTimerDelay(100); //Not sure if this is needed
	CC110L_WriteConfig(CC110L_Config);
	CC110L_WritePATable(1, PA_TABLE0);
	return 0;
}


