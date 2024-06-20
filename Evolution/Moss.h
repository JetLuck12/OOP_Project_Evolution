#pragma once
#include "Plant.h"

class Moss : public Plant
{
public:
	Moss(size_t ttl, const Coord& coord, const Texture& tex):Plant(ttl, coord, tex){}
	~Moss() override = default;
	size_t get_ttl_if_eaten() override { return ttl_if_eaten; }
private:
	static size_t ttl_if_eaten;
	static size_t breeding_period;
	bool is_cell_is_suitable(Creature_data& data, const Coord& coord) override;
	void breed_one(Creature_data& field, const Coord& coord) override;
	bool is_breedable() const override;
};