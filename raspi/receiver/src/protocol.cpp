/*
 * protocol.c
 *
 *  Created on: 09.03.2016
 *      Author: Richard Treichl
 */

#include "protocol.h"
#include "../driver/driver.h"

#include <string.h>
#include <iostream>
#include <iomanip>

int32_t protocol_get_data(PROTOCOL_BUFFER_STC *buffer, uint8_t size, bool sign);

int protocol_decoder(PROTOCOL_DATA_STC *protocol, DATABASE_DATA_STC *data)
{
	memset(data, 0, sizeof(DATABASE_DATA_STC));
	data->header.addr = protocol->header.src_addr;
	memcpy(&data->hardware, &protocol->hardware, sizeof(data->hardware));
	data->header.status = protocol->header.status;
	protocol->buffer.size = 0;
	protocol->header.length = sizeof(PROTOCOL_HEADER_STC) + sizeof(PROTOCOL_HARDWARE_STC);

	if(protocol->hardware.solar) {
		data->solar.voltage = SOLAR_VOLT_FACTOR * protocol_get_data(&protocol->buffer, 2, false);
	}

	if(protocol->hardware.max17048) {
		data->max17048.charge = protocol_get_data(&protocol->buffer, 2, false) * MAX17048_CHARGE_FACTOR;
		data->max17048.c_rate = protocol_get_data(&protocol->buffer, 2, true) * MAX17048_CRATE_FACTOR;
		data->max17048.voltage = protocol_get_data(&protocol->buffer, 2, false) * MAX17048_VCELL_FACTOR;
	}

	if(protocol->hardware.si1147) {
		data->si1147.ir = protocol_get_data(&protocol->buffer, 2, false) * SI1147_IR_FACTOR;
		data->si1147.uv = protocol_get_data(&protocol->buffer, 2, false) * SI1147_UV_FACTOR;
		data->si1147.vis = protocol_get_data(&protocol->buffer, 2, false) * SI1147_VIS_FACTOR;
	}

	if(protocol->hardware.hdc1000) {
		data->hdc1000.temp = protocol_get_data(&protocol->buffer, 2, false) * HDC1000_TEMP_FACTOR ;
		data->hdc1000.humi = protocol_get_data(&protocol->buffer, 2, false) * HDC1000_HUMI_FACTOR ;
	}

	if(protocol->hardware.tmp102) {
		data->tmp102.temp = protocol_get_data(&protocol->buffer, 2, true) * TMP102_TEMP_FACTOR;
	}

	if(protocol->hardware.lps25h) {
		data->lps25h.press =  protocol_get_data(&protocol->buffer, 4, false) * LPS25H_PRESS_FACTOR;
		data->lps25h.temp = protocol_get_data(&protocol->buffer, 2, true) * LPS25H_TEMP_FACTOR;
	}

	if(protocol->hardware.ds18b20) {
		data->ds18b20.temp = DS18B20_TEMP_FACTOR * protocol_get_data(&protocol->buffer, 2, true);;
	}

	data->header.rssi = 1.0 * CC110L::RssiConvertion(protocol_get_data(&protocol->buffer, 1, false));
	data->header.crc = protocol_get_data(&protocol->buffer, 1, false);

	if(protocol->header.length == protocol->buffer.size) {
		return 0;
	}

	return -1;
}

int32_t protocol_print_data(DATABASE_DATA_STC *data)
{
	time_t rawtime;
	time(&rawtime);
	string t = ctime(&rawtime);
	t.insert(0, "  ");
	std::cout << std::endl;
	std::cout << "+" << std::setfill('-') << std::setw(41) << "+" << std::endl;
	std::cout << std::setfill(' ');
	std::cout << "|" << std::setw(30) << std::left << "Received Sensor Data:" << std::setw(11) << std::right << "|" << std::endl;
	std::cout << "|" << std::setw(41) << std::right << "|" << std::endl;
	std::cout << "|" << std::setw(20) << std::left << "Header:" << std::setw(21) << std::right << "|" << std::endl;
	std::cout << "|" << std::setw(30) << std::left << t.substr(0,t.length()-1) << std::setw(11) << std::right << "|" << std::endl;
	std::cout << "|" << std::setw(20) << std::left << "  Address:" << std::setw(19) << std::right << "0x" << std::hex << static_cast<int>(data->header.addr) << "|" << std::endl;
	std::cout << "|" << std::setw(20) << std::left << "  Status:" << std::setw(19) << std::right << "0x" << std::hex << static_cast<int>(data->header.status) << "|" << std::endl;
	std::cout << "|" << std::setw(20) << std::left << "  RSSI: " << std::setw(17) << std::right << data->header.rssi << "dBm" << "|" << std::endl;
	std::cout << "|" << std::setw(20) << std::left << "  CRC:";
	if (data->header.crc & 0x80)
		std::cout << std::setw(20) << std::right << "Ok";
	else
		std::cout << std::setw(20) << std::right << "Failed";
	std::cout << "|" << std::endl;

	std::cout << "|" << std::setw(41) << std::right << "|" << std::endl;
	std::cout << "|" << std::setw(20) << std::left << "Hardware:" << std::setw(21) << std::right << "|" << std::endl;
	std::cout << "|" << std::setw(20) << std::left << "  Solar:" << std::setw(20) << std::right << std::boolalpha << static_cast<bool>(data->hardware.solar) << "|" << std::endl;
	std::cout << "|" << std::setw(20) << std::left << "  MAX17048:" << std::setw(20) << std::right << std::boolalpha << static_cast<bool>(data->hardware.max17048) << "|" << std::endl;
	std::cout << "|" << std::setw(20) << std::left << "  HDC1000:" << std::setw(20) << std::right << std::boolalpha << static_cast<bool>(data->hardware.hdc1000) << "|" << std::endl;
	std::cout << "|" << std::setw(20) << std::left << "  TMP102:" << std::setw(20) << std::right << std::boolalpha << static_cast<bool>(data->hardware.tmp102) << "|" << std::endl;
	std::cout << "|" << std::setw(20) << std::left << "  LPS25H:" << std::setw(20) << std::right << std::boolalpha << static_cast<bool>(data->hardware.lps25h) << "|" << std::endl;
	std::cout << "|" << std::setw(20) << std::left << "  DS18B20:" << std::setw(20) << std::right << std::boolalpha << static_cast<bool>(data->hardware.ds18b20) << "|" << std::endl;
	std::cout << "|" << std::setw(20) << std::left << "  SI1147:" << std::setw(20) << std::right << std::boolalpha << static_cast<bool>(data->hardware.si1147) << "|" << std::endl;

	if(data->hardware.solar) {
		std::cout << "|" << std::setw(41) << std::right << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "Solar:" << std::setw(21) << std::right << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "  Voltage:" << std::setw(19) << std::right << data->solar.voltage << "V" << "|" << std::endl;
	}

	if(data->hardware.max17048) {
		std::cout << "|" << std::setw(41) << std::right << "|" << std::endl;
		std::cout << "|" << std::setw(30) << std::left << "Max17048 (aka) Battery:" << std::setw(11) << std::right << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "  Voltage:" << std::setw(19) << std::right << data->max17048.voltage << "V" << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "  Charge:" << std::setw(19) << std::right << data->max17048.charge << "%" << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "  Charging Rate:" << std::setw(16) << std::right << data->max17048.c_rate << "%/hr" << "|" << std::endl;
	}

	if(data->hardware.hdc1000) {
		std::cout << "|" << std::setw(41) << std::right << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "HDC1000:" << std::setw(21) << std::right << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "  Temperature:" << std::setw(18) << std::right << data->hdc1000.temp << "\u00b0C" << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "  Humidity:" << std::setw(19) << std::right << data->hdc1000.humi << "%" << "|" << std::endl;
	}

	if(data->hardware.tmp102) {
		std::cout << "|" << std::setw(41) << std::right << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "TMP102:" << std::setw(21) << std::right << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "  Temperature:" << std::setw(18) << std::right << data->tmp102.temp << "\u00b0C" << "|" << std::endl;
	}

	if(data->hardware.lps25h) {
		std::cout << "|" << std::setw(41) << std::right << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "LPS25H:" << std::setw(21) << std::right << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "  Temperature:" << std::setw(18) << std::right << data->lps25h.temp << "\u00b0C" << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "  Pressure:" << std::setw(17) << std::right << data->lps25h.press << "hPa" << "|" << std::endl;
	}

	if(data->hardware.ds18b20) {
		std::cout << "|" << std::setw(41) << std::right << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "DS18B20:" << std::setw(21) << std::right << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "  Temperatur:" << std::setw(18) << std::right << data->ds18b20.temp << "\u00b0C" << "|" << std::endl;
	}

	if(data->hardware.si1147) {
		std::cout << "|" << std::setw(41) << std::right << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "SI1147:" << std::setw(21) << std::right << "|" << std::endl;;
		std::cout << "|" << std::setw(20) << std::left << "  Infrared:" << std::setw(17) << std::right << data->si1147.ir << "lux" << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "  Visible:" << std::setw(17) << std::right << data->si1147.vis << "lux" << "|" << std::endl;
		std::cout << "|" << std::setw(20) << std::left << "  Ultra Violet:" << std::setw(20) << std::right << data->si1147.uv << "|" << std::endl;
	}
	std::cout << "+" << std::setfill('-') << std::setw(41) << "+" << std::endl;
	std::cout << std::setfill(' ');
	std::cout << std::endl;
	return 0;
}

int32_t protocol_get_data(PROTOCOL_BUFFER_STC *buffer, uint8_t size, bool sign)
{
	int32_t tmp = 0;
	memcpy(&tmp, &buffer->data[buffer->size], size);
	if((0x80 << (8 * (size - 1)) & tmp) && sign) {
		tmp = tmp | (0xFFFFFFFF << (size * 8));
	}
	buffer->size += size;
	return tmp;
}
