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

int Database::UpdateAvg(uint8_t protocol, uint8_t address, void *data)
{
	string query = mysql_select_sensorsavgmaxmin;
	ReplaceString("SensorsAvg", query);
	ReplaceDecimal(address, query);
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	if(mysql_num_rows(this->Result) == 0){
		InsertMinMaxAvg(2, protocol, address, data);
	}
	else {
		query.assign(mysql_update_sensorsavg);
		ReplaceDecimal(address, query);
		switch(protocol) {
			case 1:
				{
					PROTOCOL_PORT_1_DATA_STC *data_1 = (PROTOCOL_PORT_1_DATA_STC*) data;
//					ReplaceFloat(data_1->hdc1000_temp / 100.0, query);
//					ReplaceFloat(data_1->hdc1000_humi / 100.0, query);
//					ReplaceFloat(data_1->tmp102_temp / 100.0, query);
//					ReplaceFloat(data_1->lps25h_temp / 100.0, query);
//					ReplaceFloat(data_1->lps25h_press / 100.0, query);
//					ReplaceFloat(data_1->si1147_uv / 100.0, query);
//					ReplaceFloat(data_1->si1147_vis * 1.0, query);
//					ReplaceFloat(data_1->si1147_ir * 1.0, query);
//					ReplaceFloat(data_1->vbat / 100.0, query);
//					ReplaceFloat(data_1->vsolar / 100.0, query);
				}
				break;
			case 2:
				{
					PROTOCOL_PORT_2_DATA_STC *data_2 = (PROTOCOL_PORT_2_DATA_STC*) data;
//					ReplaceFloat(data_2->hdc1000_temp / 100.0, query);
//					ReplaceFloat(data_2->hdc1000_humi / 100.0, query);
//					ReplaceFloat(data_2->tmp102_temp / 100.0, query);
//					ReplaceFloat(data_2->lps25h_temp / 100.0, query);
//					ReplaceFloat(data_2->lps25h_press / 100.0, query);
//					ReplaceFloat(data_2->vbat / 100.0, query);
//					ReplaceFloat(data_2->vsolar / 100.0, query);
				}
				break;
			case 3:
				{
					PROTOCOL_PORT_3_DATA_STC *data_3 = (PROTOCOL_PORT_3_DATA_STC*) data;
//					ReplaceFloat(data_3->hdc1000_temp / 100.0, query);
//					ReplaceFloat(data_3->hdc1000_humi / 100.0, query);
//					ReplaceFloat(data_3->tmp102_temp / 100.0, query);
//					ReplaceFloat(data_3->si1147_uv / 100.0, query);
//					ReplaceFloat(data_3->si1147_vis * 1.0, query);
//					ReplaceFloat(data_3->si1147_ir * 1.0, query);
//					ReplaceFloat(data_3->vbat / 100.0, query);
//					ReplaceFloat(data_3->vsolar / 100.0, query);
				}
				break;
			case 4:
				{
					PROTOCOL_PORT_4_DATA_STC *data_4 = (PROTOCOL_PORT_4_DATA_STC*) data;
//					ReplaceFloat(data_4->hdc1000_temp / 100.0, query);
//					ReplaceFloat(data_4->hdc1000_humi / 100.0, query);
//					ReplaceFloat(data_4->tmp102_temp / 100.0, query);
//					ReplaceFloat(data_4->vbat / 100.0, query);
//					ReplaceFloat(data_4->vsolar / 100.0, query);
				}
				break;
			default:
				return -1;
		}
		MysqlQuery(query);
#if MYSQL_DEBUG
		cout << query << endl;
#endif
	}
	return 0;
}

int Database::UpdateMinMax(uint8_t minmax, uint8_t protocol, uint8_t address, void *data)
{
	string query = mysql_select_sensorsavgmaxmin;
	if(minmax == 0) {
		ReplaceString("SensorsMin", query);
	}
	else {
		ReplaceString("SensorsMax", query);
	}
	ReplaceDecimal(address, query);
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	if(mysql_num_rows(this->Result) == 0){
		InsertMinMaxAvg(minmax, protocol, address, data);
	}
	else {
		if(minmax) {
			query.assign(mysql_update_sensorsmin);
		}
		else {
			query.assign(mysql_update_sensorsmax);
		}
		ReplaceDecimal(address, query);
		switch(protocol) {
			case 1:
				{
					PROTOCOL_PORT_1_DATA_STC *data_1 = (PROTOCOL_PORT_1_DATA_STC*) data;
//					ReplaceFloat(data_1->hdc1000_temp / 100.0, query);
//					ReplaceFloat(data_1->hdc1000_temp / 100.0, query);
//					ReplaceFloat(data_1->hdc1000_humi / 100.0, query);
//					ReplaceFloat(data_1->hdc1000_humi / 100.0, query);
//					ReplaceFloat(data_1->tmp102_temp / 100.0, query);
//					ReplaceFloat(data_1->tmp102_temp / 100.0, query);
//					ReplaceFloat(data_1->lps25h_temp / 100.0, query);
//					ReplaceFloat(data_1->lps25h_temp / 100.0, query);
//					ReplaceFloat(data_1->lps25h_press / 100.0, query);
//					ReplaceFloat(data_1->lps25h_press / 100.0, query);
//					ReplaceFloat(data_1->si1147_uv / 100.0, query);
//					ReplaceFloat(data_1->si1147_uv / 100.0, query);
//					ReplaceFloat(data_1->si1147_vis * 1.0, query);
//					ReplaceFloat(data_1->si1147_vis * 1.0, query);
//					ReplaceFloat(data_1->si1147_ir * 1.0, query);
//					ReplaceFloat(data_1->si1147_ir * 1.0, query);
//					ReplaceFloat(data_1->vbat / 100.0, query);
//					ReplaceFloat(data_1->vbat / 100.0, query);
//					ReplaceFloat(data_1->vsolar / 100.0, query);
//					ReplaceFloat(data_1->vsolar / 100.0, query);
				}
				break;
			case 2:
				{
					PROTOCOL_PORT_2_DATA_STC *data_2 = (PROTOCOL_PORT_2_DATA_STC*) data;
//					ReplaceFloat(data_2->hdc1000_temp / 100.0, query);
//					ReplaceFloat(data_2->hdc1000_temp / 100.0, query);
//					ReplaceFloat(data_2->hdc1000_humi / 100.0, query);
//					ReplaceFloat(data_2->hdc1000_humi / 100.0, query);
//					ReplaceFloat(data_2->tmp102_temp / 100.0, query);
//					ReplaceFloat(data_2->tmp102_temp / 100.0, query);
//					ReplaceFloat(data_2->lps25h_temp / 100.0, query);
//					ReplaceFloat(data_2->lps25h_temp / 100.0, query);
//					ReplaceFloat(data_2->lps25h_press / 100.0, query);
//					ReplaceFloat(data_2->lps25h_press / 100.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(data_2->vbat / 100.0, query);
//					ReplaceFloat(data_2->vbat / 100.0, query);
//					ReplaceFloat(data_2->vsolar / 100.0, query);
//					ReplaceFloat(data_2->vsolar / 100.0, query);
				}
				break;
			case 3:
				{
					PROTOCOL_PORT_3_DATA_STC *data_3 = (PROTOCOL_PORT_3_DATA_STC*) data;
//					ReplaceFloat(data_3->hdc1000_temp / 100.0, query);
//					ReplaceFloat(data_3->hdc1000_temp / 100.0, query);
//					ReplaceFloat(data_3->hdc1000_humi / 100.0, query);
//					ReplaceFloat(data_3->hdc1000_humi / 100.0, query);
//					ReplaceFloat(data_3->tmp102_temp / 100.0, query);
//					ReplaceFloat(data_3->tmp102_temp / 100.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(data_3->si1147_uv / 100.0, query);
//					ReplaceFloat(data_3->si1147_vis * 1.0, query);
//					ReplaceFloat(data_3->si1147_vis * 1.0, query);
//					ReplaceFloat(data_3->si1147_ir * 1.0, query);
//					ReplaceFloat(data_3->si1147_ir * 1.0, query);
//					ReplaceFloat(data_3->vbat / 100.0, query);
//					ReplaceFloat(data_3->vbat / 100.0, query);
//					ReplaceFloat(data_3->vsolar / 100.0, query);
//					ReplaceFloat(data_3->vsolar / 100.0, query);
				}
				break;
			case 4:
				{
					PROTOCOL_PORT_4_DATA_STC *data_4 = (PROTOCOL_PORT_4_DATA_STC*) data;
//					ReplaceFloat(data_4->hdc1000_temp / 100.0, query);
//					ReplaceFloat(data_4->hdc1000_temp / 100.0, query);
//					ReplaceFloat(data_4->hdc1000_humi / 100.0, query);
//					ReplaceFloat(data_4->hdc1000_humi / 100.0, query);
//					ReplaceFloat(data_4->tmp102_temp / 100.0, query);
//					ReplaceFloat(data_4->tmp102_temp / 100.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(0.0, query);
//					ReplaceFloat(data_4->vbat / 100.0, query);
//					ReplaceFloat(data_4->vbat / 100.0, query);
//					ReplaceFloat(data_4->vsolar / 100.0, query);
//					ReplaceFloat(data_4->vsolar / 100.0, query);
				}
				break;
			default:
				return -1;
		}
		MysqlQuery(query);
#if MYSQL_DEBUG
		cout << query << endl;
#endif
	}
	return 0;
}

int Database::InsertMinMaxAvg(uint8_t minmaxavg, uint8_t protocol, uint8_t address, void *data)
{
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
	ReplaceDecimal(address, query);
	switch(protocol) {
		case 1:
			{
				PROTOCOL_PORT_1_DATA_STC *data_1 = (PROTOCOL_PORT_1_DATA_STC*) data;
//				ReplaceFloat(data_1->hdc1000_temp / 100.0, query);
//				ReplaceFloat(data_1->hdc1000_humi / 100.0, query);
//				ReplaceFloat(data_1->tmp102_temp / 100.0, query);
//				ReplaceFloat(data_1->lps25h_temp / 100.0, query);
//				ReplaceFloat(data_1->lps25h_press / 100.0, query);
//				ReplaceFloat(data_1->si1147_uv / 100.0, query);
//				ReplaceFloat(data_1->si1147_vis * 1.0, query);
//				ReplaceFloat(data_1->si1147_ir * 1.0, query);
//				ReplaceFloat(data_1->vbat / 100.0, query);
//				ReplaceFloat(data_1->vsolar / 100.0, query);
			}
			break;
		case 2:
			{
				PROTOCOL_PORT_2_DATA_STC *data_2 = (PROTOCOL_PORT_2_DATA_STC*) data;
//				ReplaceFloat(data_2->hdc1000_temp / 100.0, query);
//				ReplaceFloat(data_2->hdc1000_humi / 100.0, query);
//				ReplaceFloat(data_2->tmp102_temp / 100.0, query);
//				ReplaceFloat(data_2->lps25h_temp / 100.0, query);
//				ReplaceFloat(data_2->lps25h_press / 100.0, query);
//				ReplaceFloat(0.0, query);
//				ReplaceFloat(0.0, query);
//				ReplaceFloat(0.0, query);
//				ReplaceFloat(data_2->vbat / 100.0, query);
//				ReplaceFloat(data_2->vsolar / 100.0, query);
			}
			break;
		case 3:
			{
				PROTOCOL_PORT_3_DATA_STC *data_3 = (PROTOCOL_PORT_3_DATA_STC*) data;
//				ReplaceFloat(data_3->hdc1000_temp / 100.0, query);
//				ReplaceFloat(data_3->hdc1000_humi / 100.0, query);
//				ReplaceFloat(data_3->tmp102_temp / 100.0, query);
//				ReplaceFloat(0.0, query);
//				ReplaceFloat(0.0, query);
//				ReplaceFloat(data_3->si1147_uv / 100.0, query);
//				ReplaceFloat(data_3->si1147_vis * 1.0, query);
//				ReplaceFloat(data_3->si1147_ir * 1.0, query);
//				ReplaceFloat(data_3->vbat / 100.0, query);
//				ReplaceFloat(data_3->vsolar / 100.0, query);
			}
			break;
		case 4:
			{
				PROTOCOL_PORT_4_DATA_STC *data_4 = (PROTOCOL_PORT_4_DATA_STC*) data;
//				ReplaceFloat(data_4->hdc1000_temp / 100.0, query);
//				ReplaceFloat(data_4->hdc1000_humi / 100.0, query);
//				ReplaceFloat(data_4->tmp102_temp / 100.0, query);
//				ReplaceFloat(0.0, query);
//				ReplaceFloat(0.0, query);
//				ReplaceFloat(0.0, query);
//				ReplaceFloat(0.0, query);
//				ReplaceFloat(0.0, query);
//				ReplaceFloat(data_4->vbat / 100.0, query);
//				ReplaceFloat(data_4->vsolar / 100.0, query);
			}
			break;
		default:
			return -1;
	}
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	return 0;
}

int Database::StoreData(uint8_t protocol, uint8_t address, uint8_t status, void *data)
{
	string query;
	stringstream table;
	table << "Sensor" << (int)address << (int)protocol;
	if(MysqlTableExists(table.str()) == 0) {
		CreateSensor(protocol, address);
	}
	switch(protocol) {
	case 1:
		{
			PROTOCOL_PORT_1_DATA_STC *data_1 = (PROTOCOL_PORT_1_DATA_STC*) data;
			query.assign(mysql_insert_protocol_1_data);
//			ReplaceString(table.str(), query);
//			ReplaceFloat(data_1->hdc1000_temp / 100.0, query);
//			ReplaceFloat(data_1->hdc1000_humi / 100.0, query);
//			ReplaceFloat(data_1->tmp102_temp / 100.0, query);
//			ReplaceFloat(data_1->lps25h_temp / 100.0, query);
//			ReplaceFloat(data_1->lps25h_press / 100.0, query);
//			ReplaceFloat(data_1->si1147_uv / 100.0, query);
//			ReplaceFloat(data_1->si1147_vis * 1.0, query);
//			ReplaceFloat(data_1->si1147_ir * 1.0, query);
//			ReplaceFloat(data_1->vbat / 100.0, query);
//			ReplaceFloat(data_1->vsolar / 100.0, query);
		}
		break;
	case 2:
		{
			PROTOCOL_PORT_2_DATA_STC *data_2 = (PROTOCOL_PORT_2_DATA_STC*) data;
			query.assign(mysql_insert_protocol_1_data);
			ReplaceString(table.str(), query);
//			ReplaceFloat(data_2->hdc1000_temp / 100.0, query);
//			ReplaceFloat(data_2->hdc1000_humi / 100.0, query);
//			ReplaceFloat(data_2->tmp102_temp / 100.0, query);
//			ReplaceFloat(data_2->lps25h_temp / 100.0, query);
//			ReplaceFloat(data_2->lps25h_press / 100.0, query);
//			ReplaceFloat(data_2->vbat / 100.0, query);
//			ReplaceFloat(data_2->vsolar / 100.0, query);
		}
		break;
	case 3:
		{
			PROTOCOL_PORT_3_DATA_STC *data_3 = (PROTOCOL_PORT_3_DATA_STC*) data;
			query.assign(mysql_insert_protocol_1_data);
//			ReplaceString(table.str(), query);
//			ReplaceFloat(data_3->hdc1000_temp / 100.0, query);
//			ReplaceFloat(data_3->hdc1000_humi / 100.0, query);
//			ReplaceFloat(data_3->tmp102_temp / 100.0, query);
//			ReplaceFloat(data_3->si1147_uv / 100.0, query);
//			ReplaceFloat(data_3->si1147_vis * 1.0, query);
//			ReplaceFloat(data_3->si1147_ir * 1.0, query);
//			ReplaceFloat(data_3->vbat / 100.0, query);
//			ReplaceFloat(data_3->vsolar / 100.0, query);
		}
		break;
	case 4:
		{
			PROTOCOL_PORT_4_DATA_STC *data_4 = (PROTOCOL_PORT_4_DATA_STC*) data;
//			query.assign(mysql_insert_protocol_1_data);
//			ReplaceString(table.str(), query);
//			ReplaceFloat(data_4->hdc1000_temp / 100.0, query);
//			ReplaceFloat(data_4->hdc1000_humi / 100.0, query);
//			ReplaceFloat(data_4->tmp102_temp / 100.0, query);
//			ReplaceFloat(data_4->vbat / 100.0, query);
//			ReplaceFloat(data_4->vsolar / 100.0, query);
		}
		break;
	default:
		return -1;
	}
	MysqlQuery(query);
#if MYSQL_DEBUG
	cout << query << endl;
#endif
	UpdateAvg(protocol, address, data);
	UpdateMinMax(0, protocol, address, data);
	UpdateMinMax(1, protocol, address, data);
	query.assign(mysql_update_sensors_active);
	ReplaceDecimal(status, query);
	ReplaceDecimal(address, query);
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
	switch(protocol) {
	case 1:
		query.assign(mysql_table_protocol_1);
		break;
	case 2:
		query.assign(mysql_table_protocol_2);
		break;
	case 3:
		query.assign(mysql_table_protocol_3);
		break;
	case 4:
		query.assign(mysql_table_protocol_4);
		break;
	default:
		return -1;
	}
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

