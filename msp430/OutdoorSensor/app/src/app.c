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
	static PROTOCOL_DATA_STC data = {{0}};
	data.header.src_addr = DeviceGetAddress();
	data.header.dest_addr =  1;//Rapi address
	data.header.protocol = PROTOCOL_DATA;
	data.header.length = sizeof(PROTOCOL_HEADER_STC) + sizeof(PROTOCOL_HARDWARE_STC) - sizeof(uint8_t); //Substract one byte for the lenght byte

	application_init(&data.hardware);

	if(data.hardware.solar == 1) {
		uint16_t tmp = 0;
		tmp  = adc_getResult();
		protocol_add_data(&data.buffer, 2, &tmp);
		SystemTimerDelay(1);
	}

	if(data.hardware.max17048 == 1) {
		uint16_t tmp = 0;
		tmp = max17048_getCharge();
		protocol_add_data(&data.buffer, 2, &tmp);
		SystemTimerDelay(1);
		tmp = max17048_getChargeRate();
		protocol_add_data(&data.buffer, 2, &tmp);
		SystemTimerDelay(1);
		tmp = max17048_getVoltage();
		protocol_add_data(&data.buffer, 2, &tmp);
		SystemTimerDelay(1);
	}

	if(data.hardware.si1147 == 1) {
		uint16_t tmp = 0;
		si1147_single_conv();
		tmp = si1147_ReadRawIR();
		protocol_add_data(&data.buffer, 2, &tmp);
		SystemTimerDelay(1);
		tmp = si1147_ReadRawUV();
		protocol_add_data(&data.buffer, 2, &tmp);
		SystemTimerDelay(1);
		tmp = si1147_ReadRawVisible();
		protocol_add_data(&data.buffer, 2, &tmp);
		SystemTimerDelay(1);
	}

	if(data.hardware.hdc1000 == 1) {
		uint16_t tmp = 0;
		tmp = HDC1000_ReadRawTemperature();
		protocol_add_data(&data.buffer, 2, &tmp);
		SystemTimerDelay(1);
		tmp = HDC1000_ReadRawHumidity();
		protocol_add_data(&data.buffer, 2, &tmp);
		SystemTimerDelay(1);
	}

	if(data.hardware.tmp102 == 1) {
		uint16_t tmp = 0;
		tmp = TMP102_ReadRawTemperature();
		protocol_add_data(&data.buffer, 2, &tmp);
		SystemTimerDelay(1);
	}

	if(data.hardware.lps25h == 1) {
		uint16_t tmp = 0;
		uint32_t tmp2 = 0;
		LPS25H_OneShot();
		tmp2 = LPS25H_ReadRawPressure();
		protocol_add_data(&data.buffer, 4, &tmp2);
		SystemTimerDelay(1);
		tmp = LPS25H_ReadRawTemperature();
		protocol_add_data(&data.buffer, 2, &tmp);
		SystemTimerDelay(1);
	}

	if(data.hardware.ds18b20 == 1) {
		uint16_t tmp = 0;
		tmp = ds18b20_ReadTemperature();
		protocol_add_data(&data.buffer, 2, &tmp);
		SystemTimerDelay(1);
	}

	data.header.length = data.header.length + data.buffer.size + sizeof(uint8_t); //Add sizeof one byte for size value of dynamic data

	CC110L_SendCommand(CC110L_COMMAND_STX);
	CC110L_TX(&data, data.header.length + 1); //Due to length byte is also transmitted to the CC110L

	DeviceTurnOffinMs(1000);

	return 0;
}

uint16_t application_init(PROTOCOL_HARDWARE_STC *hw)
{
	GPIO8_OUT(GPIO8_PORT3) &= ~GPIO_PIN7;
	GPIO8_DIR(GPIO8_PORT3) |= GPIO_PIN7;

	i2c_init(1, 200);

	SPI_init(SPIMODE1);

	SystemTimerDelay(200); //Not sure if this is needed

	DeviceInitExternalHardware(hw);
	DeviceInitInternalHardware(hw);

	CC110L_SendCommand(CC110L_COMMAND_SRES);
	SystemTimerDelay(20); //Not sure if this is needed
	CC110L_WriteConfig(CC110L_Config);
	CC110L_WritePATable(1, PA_TABLE0);
	return 0;
}


