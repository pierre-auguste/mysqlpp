#ifndef CLASS_PDO_CONNECT_H_
#define CLASS_PDO_CONNECT_H_

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


class PdoConnect
{
public:

	static PdoConnect& instance();
	std::shared_ptr<sql::Connection> getDb();

private:
	// TODO function create table

	static constexpr const char* MYSQL_HOST = "localhost";
	static constexpr const char* MYSQL_DB   = "hacker";
	static constexpr const char* MYSQL_USER = "hacker";
	static constexpr const char* MYSQL_PASS = "hacker";

	PdoConnect(); // singleton
	PdoConnect(const PdoConnect&) = delete; // forbid singleton copy
	PdoConnect& operator=(const PdoConnect&) = delete; // forbid singleton copy

	std::shared_ptr<sql::Connection> db;
};

#endif /* CLASS_PDO_CONNECT_H_ */
