#pragma once
#include "Ground.h"

class Meadow : public Ground
{
public:
	Meadow(std::shared_ptr<sf::Texture> texture):texture_(texture){}
	~Meadow() override = default;
	std::shared_ptr<sf::Texture> get_texture() const override { return texture_; }
private:
	std::shared_ptr<sf::Texture> texture_;
};