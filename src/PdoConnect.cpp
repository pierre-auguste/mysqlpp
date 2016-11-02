#include "PdoConnect.h"

PdoConnect& PdoConnect::instance()
{
	static PdoConnect instance;
	return instance;
}

PdoConnect::PdoConnect()
{
	db = std::shared_ptr<sql::Connection> (
		sql::mysql::get_driver_instance()->connect(
			MYSQL_HOST,
			MYSQL_USER,
			MYSQL_PASS)
		);
	db->setSchema(MYSQL_DB);
}

std::shared_ptr<sql::Connection> PdoConnect::getDb()
{
	return db;
}
