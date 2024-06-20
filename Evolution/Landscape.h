#pragma once

class LandScape
{
public:
	LandScape() = default;
	virtual ~LandScape() = default;
	virtual size_t get_texture() const = 0;
};
