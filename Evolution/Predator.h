#pragma once

#include "Creature.h"
#include <optional>
#include <stdarg.h>

class Predator : public Creature
{
public:
	Predator(size_t ttl, const Coord& coord, const Texture& tex) :Creature(ttl, coord, tex) {}
	~Predator() override = default;
	void action(Creature_data& field) override;
protected:
	bool is_cell_is_suitable(Creature_data& data, const Coord& coord) override = 0;
	static size_t ttl_bonus_for_eat;
	static size_t ttl_breeding_level;
	std::optional<std::shared_ptr<Creature>> is_herbivirous_near(Creature_data& field);
	virtual std::optional<std::shared_ptr<Creature>> is_enemy_near(Creature_data& field) = 0;
	virtual void move(Creature_data& field, const Coord&);
	virtual void eat(Creature_data& field, std::shared_ptr<Creature>);
	virtual void breed(Creature_data& field);
	virtual void battle(Creature_data& field, std::shared_ptr<Creature> enemy);
	virtual void breed_one(Creature_data& data, const Coord& coord) = 0;
};
