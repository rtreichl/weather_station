#include <mysql/mysql.h>
#include <string>

class OWN_MYSQL
{
public:
	OWN_MYSQL();
	~OWN_MYSQL();
	int Query(const std::string &query);
	int Insert(const std::string &Fields, const void  *Values);
	int SelectTabel(const char *Tabel);
private:
	MYSQL *Connection;
	MYSQL_RES *Result;
	std::string Tabel;
	//std::string ConvertValue(string type, void *Value);
};
