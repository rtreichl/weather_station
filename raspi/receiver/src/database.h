/*
 * database.h
 *
 *  Created on: 13.01.2016
 *      Author: Richard Treichl
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <mysql/mysql.h>
#include <stdint.h>
#include <string>

typedef struct {
	uint16_t max17048:1;
	uint16_t si1147:1;
	uint16_t tmp102:1;
	uint16_t hdc1000:1;
	uint16_t lps25h:1;
	uint16_t ds18b20:1;
	uint16_t solar:1;
	uint16_t _res:9;
	//uint8_t _res2:8;
} HARDWARE_STC;

typedef struct {
	uint8_t addr;
	uint8_t status;
	uint8_t crc;
	float rssi;
} HEADER_STC;
typedef struct {
	float uv;
	float ir;
	float vis;
} SI1147_STC;
typedef struct {
	float press;
	float temp;
} LPS25H_STC;
typedef struct {
	float temp;
	float humi;
} HDC1000_STC;
typedef struct {
	float temp;
} TMP102_STC;
typedef struct {
	float temp;
} DS18B20_STC;
typedef struct {
	float voltage;
	float c_rate;
	float charge;
} MAX17048_STC;
typedef struct {
	float voltage;
} SOLAR_STC;
typedef struct {
	HEADER_STC header;
	HARDWARE_STC hardware;
	SI1147_STC si1147;
	LPS25H_STC lps25h;
	HDC1000_STC hdc1000;
	TMP102_STC tmp102;
	DS18B20_STC ds18b20;
	MAX17048_STC max17048;
	SOLAR_STC solar;
} DATABASE_DATA_STC;

class Database
{
public:
	Database();
	~Database();
	int StoreData(DATABASE_DATA_STC *data);
private:
	MYSQL *Connection;
	MYSQL_RES *Result;
	int CreateSensor(DATABASE_DATA_STC *data);
	int MysqlQuery(const std::string &query);
	int MysqlGetResult(void *data);
	int MysqlTableExists(const std::string &table);
	int MysqlTableAddIndex(const std::string &column, const std::string &table);
	int UpdateMinMax(uint8_t minmax, DATABASE_DATA_STC *data);
	int InsertMinMaxAvg(uint8_t minmaxavg, DATABASE_DATA_STC *data);
	int InsertActAvg(DATABASE_DATA_STC *data, uint32_t samples_per_hr, uint32_t hr);
	//int DynDataExtactor(DATA_STC *data, PROTOCOL_PORT_1_DATA_STC *dyn_data);
	int UpdateAvg(DATABASE_DATA_STC *data);
	int UpdateActAvgs(DATABASE_DATA_STC *data, uint32_t samples_per_hr, uint32_t hr);
	int ReplaceDecimal(int32_t number, std::string &query);
	int ReplaceFloat(float number, std::string &query);
	int ReplaceString(const std::string &str, std::string &query);
};



#endif /* DATABASE_H_ */
