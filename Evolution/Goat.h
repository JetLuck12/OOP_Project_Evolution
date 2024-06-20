#pragma once
#include "Herbivorous.h"

class Goat : public Herbivorous
{
public:
	Goat(size_t ttl, const Coord& coord, const Texture& tex):Herbivorous(ttl,coord,tex){}
	~Goat() override = default;
protected:
	static size_t ttl_breeding_level;
	void breed_one(Creature_data& data, const Coord& coord) override;
};