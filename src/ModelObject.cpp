#include "ModelObject.h"

ModelObject::ModelObject(int const& id)
{
	std::string query = "SELECT * FROM `" + getTable().getName() + "` WHERE id = ?;";
	std::unique_ptr<sql::PreparedStatement> stmt(getDb()->prepareStatement(query));
	stmt->setInt(1, id);
	stmt->execute();
	std::unique_ptr<sql::ResultSet> res(stmt->getResultSet());
	if (res->first())
	{
		this->id = id;
		name = res->getString("name");
	}
	else
	{
		throw std::runtime_error("object id was not found.");
	}
}

ModelObject::ModelObject(std::string const& name) : name(name)
{
	id = findId();
	if (id == 0)
		this->insert();
}

ModelObjects& ModelObject::getTable()
{
	return table;
}

unsigned int ModelObject::findId()
{
	std::string query = "SELECT id FROM `" + getTable().getName() + "` WHERE name = ?;";
	std::unique_ptr<sql::PreparedStatement> stmt(getDb()->prepareStatement(query));
	stmt->setString(1, name);
	stmt->execute();
	std::unique_ptr<sql::ResultSet> res(stmt->getResultSet());
	if (res->first())
		return (id = res->getInt("id"));
	return 0;
}

bool ModelObject::select()
{
	std::string query = "SELECT * FROM `" + getTable().getName() + "` WHERE name = ?;";
	std::unique_ptr<sql::PreparedStatement> stmt(getDb()->prepareStatement(query));
	stmt->setString(1, name);
	stmt->execute();
	std::unique_ptr<sql::ResultSet> res(stmt->getResultSet());
	if (res->first())
	{
		id = res->getInt("id");
		return true;
	}
	return false;
}

bool ModelObject::insert()
{
	std::string query = "INSERT INTO `" + getTable().getName() + "`(name) VALUE(?);";
	std::unique_ptr<sql::PreparedStatement> stmt(getDb()->prepareStatement(query));
	stmt->setString(1, getName());
	stmt->execute();
	setId(table.getLastInsertId()); // FIXME does a second insertion at the same time cause an ID fault ??
	return true;
}

bool ModelObject::update()
{
	std::string query = "UPDATE `" + getTable().getName() + "` SET name = ? WHERE id = ?;";
	std::unique_ptr<sql::PreparedStatement> stmt(getDb()->prepareStatement(query));
	stmt->setString(1, name);
	stmt->setInt(2, id);
	return stmt->execute();
}

ModelObject* ModelObject::setName(std::string const& name)
{
	this->name = name;
	return this;
}

std::string ModelObject::getName() const
{
	return name;
}
