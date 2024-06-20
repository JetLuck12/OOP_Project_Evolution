#include "Landscape_parser.h"

#include "Exceptions.h"

Landscape_DTO Landscape_parser::get_next(std::istream& input)
{
	std::string type;
	int x = 0, y = 0;
	if(!(input >> type >> x >> y))
	{
		throw Parser_exc{};
	}
	return Landscape_DTO{ type ,x, y};
}
