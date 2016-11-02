#include "PdoTable.h"


std::shared_ptr<sql::Connection> PdoTable::getDb() const
{
	return PdoConnect::instance().getDb();
}

std::unique_ptr<sql::ResultSet> PdoTable::fetchAll()
{
	std::unique_ptr<sql::Statement> stmt(getDb()->createStatement());
	std::string query = "SELECT * FROM `" + getName() + "`;";
	std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
	return res;
}

unsigned int PdoTable::countAll()
{
	std::unique_ptr<sql::Statement> stmt(getDb()->createStatement());
	std::string query = "SELECT count(*) FROM `" + getName() + "`;";
	std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
	res->next();
	return res->getInt64("count(*)");
}

unsigned int PdoTable::getLastInsertId() const
{
	std::unique_ptr<sql::Statement> stmt(getDb()->createStatement());
	std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT @@identity AS id"));
	res->next();
	int id = res->getInt64("id");
	return id;
}

bool PdoTable::trunkate()
{
	std::unique_ptr<sql::Statement> stmt(getDb()->createStatement());
	std::string query = "TRUNCATE TABLE `" + getName() + "`";
	return stmt->execute(query);
}
