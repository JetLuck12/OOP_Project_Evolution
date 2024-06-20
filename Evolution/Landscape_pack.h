#pragma once

#include <string>
#include <unordered_map>
#include "Landscape.h"

class Landscape_pack final 
{
public:
	Landscape_pack() = default;
	~Landscape_pack();
	void add_texture(const std::string& type, LandScape* landscape);
	LandScape* get_texture(const std::string& type) const;
private:
	std::unordered_map<std::string, LandScape*> texture_list;
};
