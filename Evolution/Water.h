#pragma once
#include "Landscape.h"

class Water : public LandScape
{
public:
	Water(size_t texture) : texture_(texture){}
	~Water() override = default;
	size_t get_texture() const override{ return texture_; }
private:
	size_t texture_;
};