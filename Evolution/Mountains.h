#pragma once
#include "Ground.h"

class Mountains : public Ground
{
public:
	Mountains(size_t texture):texture_(texture){}
	~Mountains() override = default;
	size_t get_texture() const override { return texture_; }
private:
	size_t texture_;
};