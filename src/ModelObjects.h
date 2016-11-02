// exemple of object using PDO table class

#ifndef MODEL_OBJECTS_H_
#define MODEL_OBJECTS_H_

#include <string>
#include "PdoTable.h"

//struct ModelObject;

struct ModelObjects : public PdoTable
{
public:

	ModelObjects();

	//bool insert(ModelObject object);
	std::string getName() const override; // TODO this is HOWTO set the table name


private:

	std::string const name;
};

#endif /* MODEL_OBJECTS_H_ */
