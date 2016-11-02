#include "ModelObjects.h"


ModelObjects::ModelObjects() : name("objects")
{
}

std::string ModelObjects::getName() const
{
	return name;
}

//bool ModelObjects::insert(ModelObject object)
//{
//	std::string query = "INSERT INTO `" + object.getTable().getName() + "`(name) VALUE(?);";
//	std::unique_ptr<sql::PreparedStatement> stmt(getDb()->prepareStatement(query));
//	stmt->setString(1, object.getName());
//	stmt->execute();
//	setId(object.getTable().getLastInsertId());
//	return true;
//}
