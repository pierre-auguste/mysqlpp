#include <iostream>

#include <string>
#include <vector>
#include "ModelObject.h"
//#include "ModelObjects.h"


using game = std::vector<ModelObject>;

void removePlayer(game& vec, size_t pos)
{
	//vec[pos].erase(); // delete DB row

	game::iterator it = vec.begin();
    std::advance(it, pos);
    //vec.erase(it); // delete vector entry // FIXME
}



int main() {
	try { // to play a game with DB

		// OBJECTS ROW TESTS
		game players;
		players.push_back(ModelObject("premier"));
		players.push_back(ModelObject("deuxième"));
		players.push_back(ModelObject("troisième"));
		players.push_back(ModelObject("quatrième"));

		std::cout << players[3].getName() << " has id " << players[3].getId() << std::endl;

		//players.pop_back(); // remove last player from this battle but not from DB

		size_t dead_player = 2; // We delete third player from DB
		removePlayer(players, dead_player);

		for(ModelObject player : players)
		{
			std::cout << player.getId() << ". " << player.getName()  << std::endl;
		}


		// OBJECTS TABLE TESTS
		ModelObjects objects;
		std::unique_ptr<sql::ResultSet> rows(objects.fetchAll());
		while (rows->next())
		{
			std::cout << rows->getInt("id") << ". " << rows->getString("name") << std::endl;
		}
		std::cout << "Total : " << objects.countAll() << std::endl;
		objects.trunkate();
		std::cout << "Total : " << objects.countAll() << std::endl;


	} catch (sql::SQLException &e) {
		/**
		* MySQL Connector/C++ throws three different exceptions:
		* - sql::MethodNotImplementedException (derived from sql::SQLException)
		* - sql::InvalidArgumentException (derived from sql::SQLException)
		* - sql::SQLException (derived from std::runtime_error)
		*
		* what() is derived from std::runtime_error
		*/
		std::cerr << "# ERR: SQLException in " << __FILE__;
		std::cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cerr << "# ERR: " << e.what() << std::endl;
		std::cerr << "# ERR: MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << std::endl;

		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
