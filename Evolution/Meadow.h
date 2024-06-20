#pragma once
#include "Ground.h"

class Meadow : public Ground
{
public:
	Meadow(size_t texture):texture_(texture){}
	~Meadow() override = default;
	size_t get_texture() const override { return texture_; }
private:
	size_t texture_;
};