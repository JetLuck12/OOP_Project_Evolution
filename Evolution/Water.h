#pragma once
#include "Landscape.h"

class Water : public Landscape
{
public:
	Water(std::shared_ptr<sf::Texture> texture) : texture_(texture){}
	~Water() override = default;
	std::shared_ptr<sf::Texture> get_texture() const override{ return texture_; }
private:
	std::shared_ptr<sf::Texture> texture_;
};