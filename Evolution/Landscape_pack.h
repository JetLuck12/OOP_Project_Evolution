#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "Landscape.h"

class Landscape_pack final 
{
public:
	Landscape_pack() = default;
	void add_texture(const std::string& type, std::shared_ptr<Landscape> landscape);
	std::shared_ptr<Landscape> get_texture(const std::string& type) const;
private:
	std::unordered_map<std::string, std::shared_ptr<Landscape>> texture_list;
};
