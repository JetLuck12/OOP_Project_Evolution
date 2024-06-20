#pragma once

#include <string>

#include "Texture.h"
#include <unordered_map>

class Texture_pack final
{
public:
	Texture_pack() = default;
	Texture_pack(const std::unordered_map< std::string, Texture>& texture):textures_(texture){}
	const Texture& get_texture(const std::string& key) const { return textures_.at(key); }
	void set_texture(const std::string& key, const Texture& new_tex) { textures_.at(key) = new_tex; }
	void add_texture(const std::string& key, const Texture& new_tex) { textures_.insert(std::pair{key, new_tex}); }
private:
	std::unordered_map< std::string, Texture> textures_;
};
