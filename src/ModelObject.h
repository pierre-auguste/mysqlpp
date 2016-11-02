// exemple of object using PDO row class

#ifndef MODEL_OBJECT_H_
#define MODEL_OBJECT_H_

#include <string>
#include "PdoRow.h"
#include "ModelObjects.h"


struct ModelObject : public PdoRow
{
public:

	ModelObject(int const& id);
	ModelObject(std::string const& name);

	// PDO abstract
	ModelObjects& getTable() override; // TODO this is HOWTO set the table
	unsigned int findId() override;
	bool select() override;
	bool insert() override;
	bool update() override;

	// SET/GET
	ModelObject* setName(std::string const& name);
	std::string getName() const;

private:

	ModelObjects table;

	std::string name;
};



#endif /* MODEL_OBJECT_H_ */
