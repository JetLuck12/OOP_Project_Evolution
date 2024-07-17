#pragma once
#include "Ground.h"

class Mountains : public Ground
{
public:
	Mountains(std::shared_ptr<sf::Texture> texture):texture_(texture){}
	~Mountains() override = default;
	std::shared_ptr<sf::Texture> get_texture() const override { return texture_; }
private:
	std::shared_ptr<sf::Texture> texture_;
};