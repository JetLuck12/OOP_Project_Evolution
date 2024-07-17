#pragma once
#include <SFML/Graphics.hpp>


class Landscape
{
public:
	Landscape() = default;
	virtual ~Landscape() = default;
	virtual std::shared_ptr<sf::Texture> get_texture() const = 0;
};
