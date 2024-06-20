#pragma once
#include "Herbivorous.h"

class Deer : public Herbivorous
{
public:
	Deer(size_t ttl, const Coord& coord, const Texture& tex) : Herbivorous(ttl, coord, tex) {}
	~Deer() override = default;
private:
	bool is_cell_is_suitable(Creature_data& data, const Coord& coord) override;
	void breed_one(Creature_data& data, const Coord& coord) override;
};
