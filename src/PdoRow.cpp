#include "PdoRow.h"

std::shared_ptr<sql::Connection> PdoRow::getDb() const
{
	return PdoConnect::instance().getDb();
}

void PdoRow::setId(unsigned int const& id)
{
	this->id = id;
}

unsigned int PdoRow::getId()
{
	if (id == 0)
		id = findId();
	return id;
}

bool PdoRow::load()
{
	if (getId() == 0)
	{
		if (select())
			return true;
		else
			return insert();
	}
	return false;
}

bool PdoRow::save()
{
	if (getId() == 0)
		return insert();
	else
		return update();
}

bool PdoRow::erase()
{
	std::string query = "DELETE FROM `" + getTable().getName() + "` WHERE id = ?;";
	std::unique_ptr<sql::PreparedStatement> stmt(getDb()->prepareStatement(query));
	stmt->setInt(1, id);
	stmt->execute();
	return false;
}
