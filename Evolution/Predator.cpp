#include <random>

#include "Predator.h"
#include "Herbivorous.h"
#include "Cell.h"
#include "Creature_data.h"
#include "Ground.h"

class Creature_data;

void Predator::action(Creature_data& field)
{
	if (ttl_ >= ttl_breeding_level)
	{
		if (rand() % 2 == 1) {
			breed(field);
		}
		return;
	}

	std::optional<std::shared_ptr<Creature>> enemy = is_enemy_near(field);
	if(enemy.has_value())
	{
		move(field, enemy.value()->get_coord());
		battle(field, enemy.value());
		return;
	}

	std::optional<std::shared_ptr<Creature>> victim = is_herbivirous_near(field);
	if(victim.has_value())
	{
		move(field, victim.value()->get_coord());
		eat(field, victim.value());
	}
	else
	{
		std::vector<Coord> cells = look_around(field);
		if(!cells.empty())
		{
			move(field, cells[rand()%cells.size()]);
		}

	}
}

void Predator::breed(Creature_data& field)
{
	std::vector<Coord> cells = look_around(field);
	if (!cells.empty())
	{
		breed_one(field, cells[rand() % cells.size()]);
	}
}

void Predator::eat(Creature_data& field, std::shared_ptr<Creature> victim)
{
	ttl_ += victim->get_ttl() + ttl_bonus_for_eat;
	victim->set_ttl(0);
}

std::optional<std::shared_ptr<Creature>> Predator::is_herbivirous_near(Creature_data& field)
{
	std::vector<Coord> around_cells = look_around(field);
	std::vector<std::shared_ptr<Creature>> victims;
	for (auto cord : around_cells) {
		const Cell& cell = field.get_field().get_cell(cord);
		for (auto creature = cell.begin(); creature != cell.end(); ++creature)
		{
			if (!std::dynamic_pointer_cast<Herbivorous>(*creature))
			{
				continue;
			}
			if ((*creature)->get_ttl() != 0 && is_cell_is_suitable(field, (*creature)->get_coord())) {
				victims.push_back(*creature);
			}
		}
	}
	if (victims.empty())
	{
		return {};
	}
	return std::optional{ victims[rand() % victims.size()] };
}

void Predator::move(Creature_data& field, const Coord& coord)
{
	field.get_field().move_creature(coord, this);
}


bool Predator::is_cell_is_suitable(Creature_data& data, const Coord& coord)
{
	return !!std::dynamic_pointer_cast<Ground>(data.get_field().get_cell(coord).get_landscape());
}

void Predator::battle(Creature_data& field, std::shared_ptr<Creature> enemy)
{
	if(rand()%2)
	{
		enemy->set_ttl(0);
	}
}
