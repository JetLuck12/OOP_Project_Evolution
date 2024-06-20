#pragma once
#include <memory>

#include "Predator.h"

class Wolf : public Predator
{
public:
	Wolf(size_t ttl, const Coord& coord, const Texture& tex):Predator(ttl, coord,tex){}
	~Wolf() override = default;
private:
	bool is_cell_is_suitable(Creature_data& data, const Coord& coord) override;
	std::optional<std::shared_ptr<Creature>> is_enemy_near(Creature_data& field) override;
	void breed_one(Creature_data& data, const Coord& coord) override;
};