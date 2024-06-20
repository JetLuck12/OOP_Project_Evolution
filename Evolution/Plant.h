#pragma once
#include "Creature.h"

class Cell;

class Plant : public  Creature
{
public:
	Plant(size_t ttl,const Coord& coord, Texture tex) : Creature(ttl, coord, tex), time_after_multiply(0){}
	~Plant() override = default;
	void action(Creature_data& field) override;
	void reduce_ttl() override {}
	virtual size_t get_ttl_if_eaten() { return ttl_if_eaten; }
protected:
	bool is_cell_is_suitable(Creature_data& data, const Coord& coord) override;
	static size_t breeding_period;
	static size_t ttl_if_eaten;
	size_t time_after_multiply;
	virtual void breed_around(Creature_data& field);
	virtual void breed_one(Creature_data& field, const Coord& coord);
	static bool is_plant_here(const Cell&);
	virtual bool is_breedable() const ;
};
