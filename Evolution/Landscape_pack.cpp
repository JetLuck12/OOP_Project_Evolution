#include "Landscape_pack.h"

#include <memory>
#include <windows.h>

std::shared_ptr<Landscape> Landscape_pack::get_texture(const std::string& type) const
{
	return texture_list.at(type);
}

void Landscape_pack::add_texture(const std::string& type, std::shared_ptr<Landscape> landscape)
{
	texture_list.insert(std::pair{type, landscape});
}
