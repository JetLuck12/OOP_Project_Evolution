#pragma once
#include "Creature_DTO.h"
#include "Exceptions.h"
#include <sstream>

class Creature_parser final
{
public:
	Creature_parser() = delete;
	static Creature_DTO get_next(std::istringstream&);
};