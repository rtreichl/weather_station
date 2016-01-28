/*
 * database.cpp
 *
 *  Created on: 13.01.2016
 *      Author: Richard Treichl
 */

#include "database.h"
#include "protocol.h"
#include "mysql_commands.h"
#include <string>
#include <sstream>

#define MYSQL_DEBUG 1

using namespace std;

Database::Database()
{
	this->Connection = mysql_init(NULL);
	this->Result = NULL;
	if (this->Connection == 0)
	{
		cerr << "Error can't initialize MYSQL connection!" << endl;
	}

	if (!mysql_real_connect(this->Connection, "localhost", "root", "ArthurX1901", "WeatherStation", 0, NULL, 0))
	{
		cerr << mysql_error(this->Connection) << endl;
	}
	if(MysqlTableExists("SensorsAvg") == 0) {
		MysqlQuery(mysql_table_avg_values);
	}
	if(MysqlTableExists("SensorsMax") == 0) {
		MysqlQuery(mysql_table_max_values);
	}
	if(MysqlTableExists("SensorsMin") == 0) {
		MysqlQuery(mysql_table_min_values);
	}
	if(MysqlTableExists("SensorsActive") == 0) {
		MysqlQuery(mysql_table_sensors_active);
	}
}

int Database::DynDataExtactor(PROTOCOL_STC *data, PROTOCOL_PORT_1_DATA_STC *dyn_data)
{
	switch (data->header.protocol) {
	case PROTOCOL_1: {
		PROTOCOL_PORT_1_DATA_STC *ptr_dyn_data =
				(PROTOCOL_PORT_1_DATA_STC*) data->dyn_data;
		dyn_data->lps25h_temp = ptr_dyn_data->lps25h_temp;
		dyn_data->lps25h_press = ptr_dyn_data->lps25h_press;
		dyn_data->si1147_uv = ptr_dyn_data->si1147_uv;
		dyn_data->si1147_vis = ptr_dyn_data->si1147_vis;
		dyn_data->si1147_ir = ptr_dyn_data->si1147_ir;
	}
		break;
	case PROTOCOL_2: {
		PROTOCOL_PORT_2_DATA_STC *ptr_dyn_data =
				(PROTOCOL_PORT_2_DATA_STC*) data->dyn_data;
		dyn_data->lps25h_temp = ptr_dyn_data->lps25h_temp;
		dyn_data->lps25h_press = ptr_dyn_data->lps25h_press;
		dyn_data->si1147_uv = 0;
		dyn_data->si1147_vis = 0;
		dyn_data->si1147_ir = 0;
	}
		break;
	case PROTOCOL_3: {
		PROTOCOL_PORT_3_DATA_STC *ptr_dyn_data =
				(PROTOCOL_PORT_3_DATA_STC*) data->dyn_data;
		dyn_data->lps25h_temp = 0;
		dyn_data->lps25h_press = 0;
		dyn_data->si1147_uv = ptr_dyn_data->si1147_uv;
		dyn_data->si1147_vis = ptr_dyn_data->si1147_vis;
		dyn_data->si1147_ir = ptr_dyn_data->si1147_ir;
	}
		break;
	case PROTOCOL_4: {
		PROTOCOL_PORT_4_DATA_STC *ptr_dyn_data =
				(PROTOCOL_PORT_4_DATA_STC*) data->dyn_data;
		dyn_data->lps25h_temp = 0;
		dyn_data->lps25h_press = 0;
		dyn_data->si1147_uv = 0;
		dyn_data->si1147_vis = 0;
		dyn_data->si1147_ir = 0;
	}
		break;
	default:
		return -1;
	}
	return 0;
}

int Database::UpdateAvg(PROTOCOL_STC *data)
{
	PROTOCOL_PORT_1_DATA_STC dyn_data;
	string query = mysql_select_sensorsavgmaxmin;
	ReplaceString("SensorsAvg", query);
	ReplaceDecimal(data->header.dest_addr, query);
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	if(mysql_num_rows(this->Result) == 0){
		InsertMinMaxAvg(2, data);
	}
	else {
		query.assign(mysql_update_sensorsavg);
		DynDataExtactor(data, &dyn_data);
		ReplaceDecimal(data->header.dest_addr, query);
		ReplaceFloat(data->static_data.hdc1000_temp * HDC1000_TEMP_FACTOR, query);
		ReplaceFloat(data->static_data.hdc1000_humi * HDC1000_HUMI_FACTOR, query);
		ReplaceFloat(data->static_data.tmp102_temp * TMP102_TEMP_FACTOR, query);
		ReplaceFloat(data->static_data.max17048_vcell * MAX17048_VCELL_FACTOR, query);
		ReplaceFloat(data->static_data.max17048_charge * MAX17048_CHARGE_FACTOR, query);
		ReplaceFloat(data->static_data.max17048_crate * MAX17048_CRATE_FACTOR, query);
		ReplaceFloat(data->static_data.solar_voltage * MSP430_VSOLAR_FACTOR, query);
		ReplaceFloat(dyn_data.lps25h_temp * LPS25H_TEMP_FACTOR, query);
		ReplaceFloat(dyn_data.lps25h_press * LPS25H_PRESS_FACTOR, query);
		ReplaceFloat(dyn_data.si1147_uv * SI1147_UV_FACTOR, query);
		ReplaceFloat(dyn_data.si1147_vis * SI1147_VIS_FACTOR, query);
		ReplaceFloat(dyn_data.si1147_ir * SI1147_IR_FACTOR, query);
		MysqlQuery(query);
#if MYSQL_DEBUG
		cout << query << endl;
#endif
	}
	return 0;
}

int Database::UpdateMinMax(uint8_t minmax, PROTOCOL_STC *data)
{
	PROTOCOL_PORT_1_DATA_STC dyn_data;
	string query = mysql_select_sensorsavgmaxmin;
	if(minmax == 0) {
		ReplaceString("SensorsMin", query);
	}
	else {
		ReplaceString("SensorsMax", query);
	}
	ReplaceDecimal(data->header.dest_addr, query);
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	if(mysql_num_rows(this->Result) == 0){
		InsertMinMaxAvg(minmax, data);
	}
	else {
		if(minmax) {
			query.assign(mysql_update_sensorsmin);
		}
		else {
			query.assign(mysql_update_sensorsmax);
		}
		ReplaceDecimal(data->header.dest_addr, query);
		DynDataExtactor(data, &dyn_data);
		ReplaceFloat(data->static_data.hdc1000_temp * HDC1000_TEMP_FACTOR, query);
		ReplaceFloat(data->static_data.hdc1000_temp * HDC1000_TEMP_FACTOR, query);
		ReplaceFloat(data->static_data.hdc1000_humi * HDC1000_HUMI_FACTOR, query);
		ReplaceFloat(data->static_data.hdc1000_humi * HDC1000_HUMI_FACTOR, query);
		ReplaceFloat(data->static_data.tmp102_temp * TMP102_TEMP_FACTOR, query);
		ReplaceFloat(data->static_data.tmp102_temp * TMP102_TEMP_FACTOR, query);
		ReplaceFloat(data->static_data.max17048_vcell * MAX17048_VCELL_FACTOR, query);
		ReplaceFloat(data->static_data.max17048_vcell * MAX17048_VCELL_FACTOR, query);
		ReplaceFloat(data->static_data.max17048_charge * MAX17048_CHARGE_FACTOR, query);
		ReplaceFloat(data->static_data.max17048_charge * MAX17048_CHARGE_FACTOR, query);
		ReplaceFloat(data->static_data.max17048_crate * MAX17048_CRATE_FACTOR, query);
		ReplaceFloat(data->static_data.max17048_crate * MAX17048_CRATE_FACTOR, query);
		ReplaceFloat(data->static_data.solar_voltage * MSP430_VSOLAR_FACTOR, query);
		ReplaceFloat(data->static_data.solar_voltage * MSP430_VSOLAR_FACTOR, query);
		ReplaceFloat(dyn_data.lps25h_temp * LPS25H_TEMP_FACTOR, query);
		ReplaceFloat(dyn_data.lps25h_temp * LPS25H_TEMP_FACTOR, query);
		ReplaceFloat(dyn_data.lps25h_press * LPS25H_PRESS_FACTOR, query);
		ReplaceFloat(dyn_data.lps25h_press * LPS25H_PRESS_FACTOR, query);
		ReplaceFloat(dyn_data.si1147_uv * SI1147_UV_FACTOR, query);
		ReplaceFloat(dyn_data.si1147_uv * SI1147_UV_FACTOR, query);
		ReplaceFloat(dyn_data.si1147_vis * SI1147_VIS_FACTOR, query);
		ReplaceFloat(dyn_data.si1147_vis * SI1147_VIS_FACTOR, query);
		ReplaceFloat(dyn_data.si1147_ir * SI1147_IR_FACTOR, query);
		ReplaceFloat(dyn_data.si1147_ir * SI1147_IR_FACTOR, query);
		MysqlQuery(query);
#if MYSQL_DEBUG
		cout << query << endl;
#endif
	}
	return 0;
}

int Database::InsertMinMaxAvg(uint8_t minmaxavg, PROTOCOL_STC *data)
{
	PROTOCOL_PORT_1_DATA_STC dyn_data;
	string query;
	switch(minmaxavg) {
	case 0:
		query.assign(mysql_insert_sensorsmin);
		break;
	case 1:
		query.assign(mysql_insert_sensorsmax);
		break;
	case 2:
		query.assign(mysql_insert_sensorsavg);
		break;
	default:
		return -1;
	}
	ReplaceDecimal(data->header.dest_addr, query);
	DynDataExtactor(data, &dyn_data);
	ReplaceFloat(data->static_data.hdc1000_temp * HDC1000_TEMP_FACTOR, query);
	ReplaceFloat(data->static_data.hdc1000_humi * HDC1000_HUMI_FACTOR, query);
	ReplaceFloat(data->static_data.tmp102_temp * TMP102_TEMP_FACTOR, query);
	ReplaceFloat(data->static_data.max17048_vcell * MAX17048_VCELL_FACTOR, query);
	ReplaceFloat(data->static_data.max17048_charge * MAX17048_CHARGE_FACTOR, query);
	ReplaceFloat(data->static_data.max17048_crate * MAX17048_CRATE_FACTOR, query);
	ReplaceFloat(data->static_data.solar_voltage * MSP430_VSOLAR_FACTOR, query);
	ReplaceFloat(dyn_data.lps25h_temp * LPS25H_TEMP_FACTOR, query);
	ReplaceFloat(dyn_data.lps25h_press * LPS25H_PRESS_FACTOR, query);
	ReplaceFloat(dyn_data.si1147_uv * SI1147_UV_FACTOR, query);
	ReplaceFloat(dyn_data.si1147_vis * SI1147_VIS_FACTOR, query);
	ReplaceFloat(dyn_data.si1147_ir * SI1147_IR_FACTOR, query);
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	return 0;
}

int Database::StoreData(PROTOCOL_STC *data)
{
	PROTOCOL_PORT_1_DATA_STC dyn_data;
	string query;
	stringstream table;
	table << "Sensor" << (int)data->header.dest_addr << (int)data->header.protocol;
	if(MysqlTableExists(table.str()) == 0) {
		CreateSensor(data->header.protocol, data->header.dest_addr);
	}
	query.assign(mysql_insert_protocol_data);
	DynDataExtactor(data, &dyn_data);
	ReplaceString(table.str(), query);
	ReplaceFloat(data->static_data.hdc1000_temp * HDC1000_TEMP_FACTOR, query);
	ReplaceFloat(data->static_data.hdc1000_humi * HDC1000_HUMI_FACTOR, query);
	ReplaceFloat(data->static_data.tmp102_temp * TMP102_TEMP_FACTOR, query);
	ReplaceFloat(data->static_data.max17048_vcell * MAX17048_VCELL_FACTOR, query);
	ReplaceFloat(data->static_data.max17048_charge * MAX17048_CHARGE_FACTOR, query);
	ReplaceFloat(data->static_data.max17048_crate * MAX17048_CRATE_FACTOR, query);
	ReplaceFloat(data->static_data.solar_voltage * MSP430_VSOLAR_FACTOR, query);
	ReplaceFloat(dyn_data.lps25h_temp * LPS25H_TEMP_FACTOR, query);
	ReplaceFloat(dyn_data.lps25h_press * LPS25H_PRESS_FACTOR, query);
	ReplaceFloat(dyn_data.si1147_uv * SI1147_UV_FACTOR, query);
	ReplaceFloat(dyn_data.si1147_vis * SI1147_VIS_FACTOR, query);
	ReplaceFloat(dyn_data.si1147_ir * SI1147_IR_FACTOR, query);
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	UpdateAvg(data);
	UpdateMinMax(0, data);
	UpdateMinMax(1, data);
	query.assign(mysql_update_sensors_active);
	ReplaceDecimal(data->header.status, query);
	ReplaceDecimal(data->header.dest_addr, query);
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	return 0;
}

int Database::ReplaceString(const string &str, std::string &query)
{
	query.replace(query.find("%s"), 2, str);
	return 0;
}

int Database::ReplaceDecimal(uint8_t number, std::string &query)
{
	char replace[2];
	replace[0] = '0' + number;
	replace[1] = 0;
	query.replace(query.find("%d" , 0, 2), 2, replace);
	return 0;
}

int Database::ReplaceFloat(float number, std::string &query)
{
	stringstream num;
	num.precision(2);
	num << fixed << number;
	query.replace(query.find("%f", 0, 2), 2, num.str());
	return 0;
}

int Database::CreateSensor(uint8_t protocol, uint8_t address)
{
	string query;
	stringstream table;
	table << "Sensor" << (int)address << (int)protocol;
	query.assign(mysql_table_protocol);
	ReplaceString(table.str(), query);
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	query.assign(mysql_insert_sensors_active);
	ReplaceString(table.str(), query);
	ReplaceDecimal(address, query);
	ReplaceDecimal(protocol, query);
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	return 0;
}

int Database::MysqlTableExists(const string &table)
{
	uint8_t rows = 0;
	string query = mysql_table_exists;
	ReplaceString(table, query);
	MysqlQuery(query);
	rows = mysql_num_rows(this->Result);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	if(rows != 0) {
#if MYSQL_DEBUG
		cout << "Table: '" << table << "' already exists!!" << endl;
#endif
		return 1;
	}
	return 0;
}

int Database::MysqlQuery(const string &query)
{
	mysql_free_result(this->Result);
	if (mysql_query(this->Connection, query.c_str())) {
		cerr << mysql_error(this->Connection) << endl;
		return -1;
	}
	this->Result = mysql_store_result(this->Connection);
	return 0;
}

int Database::MysqlTableAddIndex(const string &column, const std::string &table)
{
	string query =  mysql_colum_as_index;
	ReplaceString(table, query);
	ReplaceString(column, query);
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	return 0;
}

int Database::MysqlGetResult(void *data)
{
	return 0;
}

Database::~Database()
{
	mysql_close(this->Connection);
}

