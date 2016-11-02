#ifndef CLASS_PDO_ROW_H_
#define CLASS_PDO_ROW_H_

#include "PdoConnect.h"
#include "PdoTable.h"

class PdoRow
{
public :

	virtual ~PdoRow() {};

	// EXTRACT THESE
	virtual PdoTable& getTable(void) =0;
	virtual unsigned int findId(void) =0;
	virtual bool select(void) =0;
	virtual bool insert(void) =0;
	virtual bool update(void) =0;

	// USE THESE
	bool load(); // select or insert
	bool save(); // update or insert
	bool erase(); // delete

	// SET / GET
	void setId(unsigned int const& id);
	unsigned int getId(); // return or set row id

protected :

	std::shared_ptr<sql::Connection> getDb() const; // return MySql connexion

	unsigned int id; // row id
	// todo _ct
	// todo _ut
};

#endif /* CLASS_PDO_ROW_H_ */
