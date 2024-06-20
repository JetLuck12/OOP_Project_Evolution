#pragma once
#include <memory>

#include "Predator.h"

class Lynx : public Predator
{
public:
	Lynx(size_t ttl, const Coord& coord, const Texture& tex):Predator(ttl,coord,tex){}
	~Lynx() override = default;
private:
	static size_t ttl_bonus_for_eat;
	bool is_cell_is_suitable(Creature_data& data, const Coord& coord) override;
	std::optional<std::shared_ptr<Creature>> is_enemy_near(Creature_data& field) override;
	void breed_one(Creature_data& data, const Coord& coord) override;
};