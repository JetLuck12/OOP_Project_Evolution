#pragma once

class Landscape
{
public:
	Landscape() = default;
	virtual ~Landscape() = default;
	virtual size_t get_texture() const = 0;
};
