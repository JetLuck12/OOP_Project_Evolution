#pragma once

#include <string>

#include <SFML/Graphics.hpp>
#include <unordered_map>

class Texture_pack final
{
public:
	Texture_pack() = default;
	Texture_pack(const std::unordered_map< std::string, std::shared_ptr<sf::Texture>>& texture):textures_(texture){}
	std::shared_ptr<sf::Texture> get_texture(const std::string& key) const { return textures_.at(key); }
	void set_texture(const std::string& key, std::shared_ptr<sf::Texture> new_tex) { textures_.at(key) = new_tex; }
	void add_texture(const std::string& key, std::shared_ptr<sf::Texture> new_tex) { textures_.insert(std::pair{key, new_tex}); }
private:
	std::unordered_map< std::string, std::shared_ptr<sf::Texture>> textures_;
};
