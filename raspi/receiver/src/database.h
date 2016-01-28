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
#include <iostream>

class Database
{
public:
	Database();
	~Database();
	int StoreData(uint8_t  protocol, uint8_t address, uint8_t status, void *data);
private:
	MYSQL *Connection;
	MYSQL_RES *Result;
	int CreateSensor(uint8_t protocol, uint8_t address);
	int MysqlQuery(const std::string &query);
	int MysqlGetResult(void *data);
	int MysqlTableExists(const std::string &table);
	int MysqlTableAddIndex(const std::string &column, const std::string &table);
	int UpdateMinMax(uint8_t minmax, uint8_t protocol, uint8_t address, void *data);
	int InsertMinMaxAvg(uint8_t minmaxavg, uint8_t protocol, uint8_t address, void *data);
	int UpdateAvg(uint8_t protocol, uint8_t address, void *data);
	int ReplaceDecimal(uint8_t number, std::string &query);
	int ReplaceFloat(float number, std::string &query);
	int ReplaceString(const std::string &str, std::string &query);
};



#endif /* DATABASE_H_ */
