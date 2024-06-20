#include "Creature_parser.h"
#include <sstream>

Creature_DTO Creature_parser::get_next(std::istringstream& stream)
{
	std::string type;
	int x = 0, y = 0, z = 0, ttl = 0;
	if(!(stream >> type >> ttl >> x >> y >> z))
	{
		throw Parser_exc{};
	}
	return Creature_DTO{ type,ttl, x, y, z};
}
