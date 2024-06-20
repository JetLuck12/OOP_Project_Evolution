#pragma once
#include "Plant.h"

class Grass : public Plant
{
public:
	Grass(size_t ttl, const Coord& coord, const Texture& tex):Plant(ttl,coord,tex){}
	~Grass() override = default;
private:
	bool is_cell_is_suitable(Creature_data& data, const Coord& coord) override;
	void breed_one(Creature_data& field, const Coord& coord) override;
};
