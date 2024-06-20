#pragma once
#include "Landscape_DTO.h"
#include <sstream>

class Landscape_parser
{
public:
	Landscape_parser() = delete;
	static Landscape_DTO get_next(std::istream&);
};
