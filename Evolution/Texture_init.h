#pragma once
#include <memory>
#include <memory>

#include "TexturePack.h"
#include "fstream"
#include "Meadow.h"
#include "Mountains.h"
#include "sstream"
#include "Water.h"

inline Texture_pack texture_init()
{
	std::ifstream paths("texture_paths.txt");
	std::string line;
	Texture_pack textures;
	while (std::getline(paths, line))
	{
		std::stringstream streamline(line);
		std::string type, path;

		streamline >> type >> path;
		sf::Texture tex;
		tex.loadFromFile(path);
		textures.add_texture(type, std::make_shared<sf::Texture>(tex));
	}
	return textures;
}

inline Landscape_pack landscape_init()
{
	std::ifstream paths("landscape_paths.txt");
	std::string line;
	Landscape_pack textures;
	while (std::getline(paths, line))
	{
		std::stringstream streamline(line);
		std::string type, path;

		streamline >> type >> path;
		sf::Texture tex;
		tex.loadFromFile(path);
		tex.setSmooth(true);
		tex.setRepeated(true);
		if(type == "Meadow")
		{
			textures.add_texture(type, std::make_shared<Meadow>(std::make_shared<sf::Texture>(tex)));
		}
		else if (type == "Water")
		{
			textures.add_texture(type, std::make_shared<Water>(std::make_shared<sf::Texture>(tex)));
		}
		else if (type == "Mountain")
		{
			textures.add_texture(type, std::make_shared<Mountains>(std::make_shared<sf::Texture>(tex)));
		}
		
	}
	return textures;
}
