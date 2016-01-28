#include "mysql.h"
#include <iostream>
#include <sstream>
#include <stdint.h>


using namespace std;

std::string trim(std::string const& str)
{
	string word;
	uint8_t first, last;
	first = str.find_first_not_of(' ');
	last = str.find_last_not_of(' ');
	word = str.substr(first, last+1);
	return word;
}

OWN_MYSQL::OWN_MYSQL()
{	
	this->Connection = mysql_init(NULL);
	if (this->Connection == 0)
	{
		cerr << "Error can't initialize MYSQL connection!" << endl;
	}
		
	if (!mysql_real_connect(this->Connection, "localhost", "root", "ArthurX1901", "WeatherStation", 0, NULL, 0)) 
	{
		cerr << mysql_error(this->Connection) << endl;
	}
}

int OWN_MYSQL::Insert(const string &Fields, const void  *Values)
{
	string query_string("INSERT INTO ");
	query_string += this->Tabel + "( ";
	std::string delimiter = ",";
	string query_values;
	string WorkingFields = Fields;
	string Field;
	string Name;
	string Type;
	uint8_t pos;
	uint8_t num = 0;
	int *Value = (int *)Values;
	void *Value2 = 0;
	ostringstream convert;
	
	while (!WorkingFields.empty())
	{
		pos = WorkingFields.find(delimiter);
		if (pos != -1)
		{
			Field = trim(WorkingFields.substr(0, pos));
			WorkingFields.erase(0, pos + delimiter.length());
		}
		else
		{
			Field = trim(WorkingFields.substr(0, WorkingFields.length()));
			WorkingFields.erase();
		}
		Type = trim(Field.substr(0, Field.find(' ')));
		Name = trim(Field.substr(Field.find(' '), Field.length()));
		if (Type == "uint32_t")
		{
			convert << *(uint32_t *)Value[num];
			//Value = static_cast<uint32_t*>(Value) + 1;
		}
		else if (Type == "float")
		{
			convert << *(float *)Value[num];
			//Value = static_cast<float*>(Value) + 1;
		}
		else if (Type == "int32_t")
		{
			convert << *(int32_t *)Value[num];
			//Value = static_cast<int32_t*>(Value) + 1;
		}
		else if (Type == "string")
		{
			convert << *(string *)Value[num];
			//Value = static_cast<int32_t*>(Value) + 1;
		}
		query_values += " '" + convert.str() + "',";
		query_string += " " + Name + ",";
		convert.str("");
		convert.clear();
		num++;
		
	}
	query_string = query_string.substr(0, query_string.length() - 1);
	query_values = query_values.substr(0, query_values.length() - 1);
	query_string += " ) VALUES ( " + query_values + " )";
	cout << query_string << endl;
	if (mysql_query(this->Connection, query_string.c_str())) {
		cerr << mysql_error(this->Connection) << endl;
		return 1;
	}

	return 0;
}

int OWN_MYSQL::SelectTabel(const char *Tabel)
{
	this->Tabel = Tabel;
	return 0;
}

int OWN_MYSQL::Query(const string &query)
{
	if (mysql_query(this->Connection, query.c_str())) {
		cerr << mysql_error(this->Connection) << endl;
		return 1;
	}
	return 0;
}

OWN_MYSQL::~OWN_MYSQL()
{
	mysql_close(this->Connection);
}
