#pragma once
#include "Creature.h"
#include <optional>
#include <memory>

class Herbivorous : public Creature
{
public:
	Herbivorous(size_t ttl, const Coord& coord, const Texture& tex):Creature(ttl, coord, tex){}
	~Herbivorous() override = default;
	void action(Creature_data& field) override;
protected:
	bool is_cell_is_suitable(Creature_data& data, const Coord& coord) override;
	static size_t ttl_breeding_level;
	virtual void eat(Creature_data& field, std::shared_ptr <Creature>);
	virtual void breed(Creature_data& field);
	virtual void breed_one(Creature_data& data, const Coord& coord);
	virtual void move(Creature_data& field, const Coord&);
	virtual std::optional<Coord> is_predator_near(Creature_data& field);
	virtual std::optional<std::shared_ptr<Creature>> is_plant_near(Creature_data& field);
	virtual std::optional<std::shared_ptr<Creature>> is_plant_here(Creature_data& field);
};