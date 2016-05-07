/*
 * database.cpp
 *
 *  Created on: 13.01.2016
 *      Author: Richard Treichl
 */

#include <string>
#include <sstream>
#include <iostream>

#include "database.h"
#include "mysql_commands.h"

#define MYSQL_DEBUG 0

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
	if(MysqlTableExists("SensorsActAvg") == 0) {
		MysqlQuery(mysql_table_act_avg_values);
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

int Database::UpdateAvg(DATABASE_DATA_STC *data)
{
	//PROTOCOL_PORT_1_DATA_STC dyn_data;
	string query = mysql_select_sensorsavgmaxmin;
	ReplaceString("SensorsAvg", query);
	ReplaceDecimal(data->header.addr, query);
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	if(mysql_num_rows(this->Result) == 0){
		InsertMinMaxAvg(2, data);
	}
	else {
		query.assign(mysql_update_sensorsavg);
		//DynDataExtactor(data, &dyn_data);
		ReplaceDecimal(data->header.addr, query);
		ReplaceFloat(data->hdc1000.temp, query);
		ReplaceFloat(data->hdc1000.humi, query);
		ReplaceFloat(data->tmp102.temp, query);
		ReplaceFloat(data->max17048.voltage, query);
		ReplaceFloat(data->max17048.charge, query);
		ReplaceFloat(data->max17048.c_rate, query);
		ReplaceFloat(data->solar.voltage, query);
		ReplaceFloat(data->lps25h.temp, query);
		ReplaceFloat(data->lps25h.press, query);
		ReplaceFloat(data->si1147.uv, query);
		ReplaceFloat(data->si1147.vis, query);
		ReplaceFloat(data->si1147.ir, query);
		ReplaceFloat(data->header.rssi * 1.0, query);
		MysqlQuery(query);
#if MYSQL_DEBUG
		cout << query << endl;
#endif
	}
	return 0;
}

int Database::UpdateActAvgs(DATABASE_DATA_STC *data, uint32_t samples_per_hr, uint32_t hr)
{
	//PROTOCOL_PORT_1_DATA_STC dyn_data;
	string query = mysql_select_sensorsactavg;
	ReplaceDecimal(data->header.addr, query);
	ReplaceDecimal(samples_per_hr * hr, query);
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	if(mysql_num_rows(this->Result) == 0){
		InsertActAvg(data, samples_per_hr, hr);
	}
	else {
		query.assign(mysql_update_sensors_act_avgs);
		//DynDataExtactor(data, &dyn_data);
		ReplaceDecimal(data->header.addr, query);
		ReplaceDecimal(samples_per_hr * hr, query);
		ReplaceFloat(data->hdc1000.temp, query);
		ReplaceFloat(data->hdc1000.humi, query);
		ReplaceFloat(data->tmp102.temp, query);
		ReplaceFloat(data->max17048.voltage, query);
		ReplaceFloat(data->max17048.charge, query);
		ReplaceFloat(data->max17048.c_rate, query);
		ReplaceFloat(data->solar.voltage, query);
		ReplaceFloat(data->lps25h.temp, query);
		ReplaceFloat(data->lps25h.press, query);
		ReplaceFloat(data->si1147.uv, query);
		ReplaceFloat(data->si1147.vis, query);
		ReplaceFloat(data->si1147.ir , query);
		ReplaceFloat(data->header.rssi * 1.0, query);
		MysqlQuery(query);
#if MYSQL_DEBUG
		cout << query << endl;
#endif
	}
	return 0;
}

int Database::UpdateMinMax(uint8_t minmax, DATABASE_DATA_STC *data)
{
	//PROTOCOL_PORT_1_DATA_STC dyn_data;
	string query = mysql_select_sensorsavgmaxmin;
	if(minmax == 0) {
		ReplaceString("SensorsMin", query);
	}
	else {
		ReplaceString("SensorsMax", query);
	}
	ReplaceDecimal(data->header.addr, query);
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
		ReplaceDecimal(data->header.addr, query);
		//DynDataExtactor(data, &dyn_data);
		ReplaceFloat(data->hdc1000.temp, query);
		ReplaceFloat(data->hdc1000.temp, query);
		ReplaceFloat(data->hdc1000.humi, query);
		ReplaceFloat(data->hdc1000.humi, query);
		ReplaceFloat(data->tmp102.temp, query);
		ReplaceFloat(data->tmp102.temp, query);
		ReplaceFloat(data->max17048.voltage, query);
		ReplaceFloat(data->max17048.voltage, query);
		ReplaceFloat(data->max17048.charge, query);
		ReplaceFloat(data->max17048.charge, query);
		ReplaceFloat(data->max17048.c_rate, query);
		ReplaceFloat(data->max17048.c_rate, query);
		ReplaceFloat(data->solar.voltage, query);
		ReplaceFloat(data->solar.voltage, query);
		ReplaceFloat(data->lps25h.temp, query);
		ReplaceFloat(data->lps25h.temp, query);
		ReplaceFloat(data->lps25h.press, query);
		ReplaceFloat(data->lps25h.press, query);
		ReplaceFloat(data->si1147.uv, query);
		ReplaceFloat(data->si1147.uv, query);
		ReplaceFloat(data->si1147.vis, query);
		ReplaceFloat(data->si1147.vis, query);
		ReplaceFloat(data->si1147.ir, query);
		ReplaceFloat(data->si1147.ir, query);
		ReplaceFloat(data->header.rssi, query);
		ReplaceFloat(data->header.rssi, query);
		MysqlQuery(query);
#if MYSQL_DEBUG
		cout << query << endl;
#endif
	}
	return 0;
}

int Database::InsertMinMaxAvg(uint8_t minmaxavg, DATABASE_DATA_STC *data)
{
	//PROTOCOL_PORT_1_DATA_STC dyn_data;
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
	ReplaceDecimal(data->header.addr, query);
	//DynDataExtactor(data, &dyn_data);
	ReplaceFloat(data->hdc1000.temp, query);
	ReplaceFloat(data->hdc1000.humi, query);
	ReplaceFloat(data->tmp102.temp, query);
	ReplaceFloat(data->max17048.voltage, query);
	ReplaceFloat(data->max17048.charge, query);
	ReplaceFloat(data->max17048.c_rate, query);
	ReplaceFloat(data->solar.voltage, query);
	ReplaceFloat(data->lps25h.temp, query);
	ReplaceFloat(data->lps25h.press, query);
	ReplaceFloat(data->si1147.uv, query);
	ReplaceFloat(data->si1147.vis, query);
	ReplaceFloat(data->si1147.ir, query);
	ReplaceFloat(data->header.rssi, query);
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	return 0;
}

int Database::InsertActAvg(DATABASE_DATA_STC *data, uint32_t samples_per_hr, uint32_t hr)
{
	//PROTOCOL_PORT_1_DATA_STC dyn_data;
	string query;
	query.assign(mysql_insert_sensorsactavg);
	ReplaceDecimal(data->header.addr, query);
	ReplaceDecimal(samples_per_hr * hr, query);
	//DynDataExtactor(data, &dyn_data);
	ReplaceFloat(data->hdc1000.temp, query);
	ReplaceFloat(data->hdc1000.humi, query);
	ReplaceFloat(data->tmp102.temp, query);
	ReplaceFloat(data->max17048.voltage, query);
	ReplaceFloat(data->max17048.charge, query);
	ReplaceFloat(data->max17048.c_rate, query);
	ReplaceFloat(data->solar.voltage, query);
	ReplaceFloat(data->lps25h.temp, query);
	ReplaceFloat(data->lps25h.press, query);
	ReplaceFloat(data->si1147.uv, query);
	ReplaceFloat(data->si1147.vis, query);
	ReplaceFloat(data->si1147.ir, query);
	ReplaceFloat(data->header.rssi * 1.0, query);
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	return 0;
}

int Database::StoreData(DATABASE_DATA_STC *data)
{
	//PROTOCOL_PORT_1_DATA_STC dyn_data;
	string query;
	stringstream table;
	table << "Sensor" << (int)data->header.addr;
	if(MysqlTableExists(table.str()) == 0) {
		CreateSensor(data);
	}
	query.assign(mysql_insert_protocol_data);
	//DynDataExtactor(data, &dyn_data);
	ReplaceString(table.str(), query);
	ReplaceFloat(data->hdc1000.temp, query);
	ReplaceFloat(data->hdc1000.humi, query);
	ReplaceFloat(data->tmp102.temp, query);
	ReplaceFloat(data->max17048.voltage, query);
	ReplaceFloat(data->max17048.charge, query);
	ReplaceFloat(data->max17048.c_rate, query);
	ReplaceFloat(data->solar.voltage, query);
	ReplaceFloat(data->lps25h.temp, query);
	ReplaceFloat(data->lps25h.press, query);
	ReplaceFloat(data->si1147.uv, query);
	ReplaceFloat(data->si1147.vis, query);
	ReplaceFloat(data->si1147.ir, query);
	ReplaceFloat(data->header.rssi * 1.0, query);
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	UpdateAvg(data);
	UpdateActAvgs(data, 90, 1); //Average over 1hr
	UpdateActAvgs(data, 90, 3); //Average over 3hr
	UpdateMinMax(0, data);
	UpdateMinMax(1, data);
	query.assign(mysql_update_sensors_active);
	ReplaceDecimal(data->header.status, query);
	ReplaceDecimal(data->header.addr, query);
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

int Database::ReplaceDecimal(int32_t number, std::string &query)
{
	ostringstream convert;
	convert << static_cast<int>(number);
	query.replace(query.find("%d" , 0, 2), 2, convert.str().c_str());
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

int Database::CreateSensor(DATABASE_DATA_STC *data)
{
	string query;
	stringstream table;
	table << "Sensor" << (int)data->header.addr;
	query.assign(mysql_table_protocol);
	ReplaceString(table.str(), query);
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	query.assign(mysql_insert_sensors_active);
	ReplaceString(table.str(), query);
	ReplaceDecimal((int)data->header.addr, query);
	ReplaceDecimal(0, query);
	ReplaceDecimal((int)data->hardware.solar, query);
	ReplaceDecimal((int)data->hardware.max17048, query);
	ReplaceDecimal((int)data->hardware.hdc1000, query);
	ReplaceDecimal((int)data->hardware.tmp102, query);
	ReplaceDecimal((int)data->hardware.lps25h, query);
	ReplaceDecimal((int)data->hardware.ds18b20, query);
	ReplaceDecimal((int)data->hardware.si1147, query);
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

