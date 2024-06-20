#include "Landscape_pack.h"

#include <windows.h>

LandScape* Landscape_pack::get_texture(const std::string& type) const
{
	return texture_list.at(type);
}

void Landscape_pack::add_texture(const std::string& type, LandScape* landscape)
{
	texture_list.insert(std::pair{type, landscape});
}

Landscape_pack::~Landscape_pack()
{
	for (auto [type, land]: texture_list)
	{
		delete land;
	}
}
