#ifndef CLASS_PDO_TABLE_H_
#define CLASS_PDO_TABLE_H_

#include "PdoConnect.h"


class PdoTable
{
public:

	virtual ~PdoTable() {};

	// EXTRACT THESE
	virtual std::string getName(void) const = 0; // return db table name

	// USE THESE
	std::unique_ptr<sql::ResultSet> fetchAll();
	unsigned int countAll();
	unsigned int getLastInsertId() const; // return mysql last insert id
	bool trunkate();

protected :

	std::shared_ptr<sql::Connection> getDb() const; // return MySql connexion
};

#endif /* CLASS_PDO_TABLE_H_ */
