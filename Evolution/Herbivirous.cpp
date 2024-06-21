#include <functional>
#include <memory>
#include <optional>
#include <span>

#include "Creature_data.h"
#include "Herbivorous.h"
#include "Plant.h"
#include "Predator.h"
#include "Cell.h"
#include "Ground.h"

class Cell;

void Herbivorous::action(Creature_data& field)
{
	std::optional<Coord> predator_coord = is_predator_near(field);
	if (predator_coord.has_value())
	{
		int x = static_cast<int>(coord_.get_x()) * 2 - static_cast<int>(predator_coord.value().get_x());
		int y = static_cast<int>(coord_.get_y()) * 2 - static_cast<int>(predator_coord.value().get_y());
		if (x < 0 || y < 0 || x >= field.get_field().get_x() || y >= field.get_field().get_y())
		{
			return;
		}
		Coord moving_coord{ coord_ * 2 - predator_coord.value() };
		if (is_cell_is_suitable(field, moving_coord))
		{
			move(field, moving_coord);
		}

	}

	if (ttl_ >= ttl_breeding_level)
	{
		breed(field);
		return;
	}

	std::optional<std::shared_ptr<Creature>> plant = is_plant_here(field);
	if (plant.has_value())
	{
		eat(field, plant.value());
		return;
	}

	plant = is_plant_near(field);
	if (plant.has_value())
	{
		move(field, plant.value()->get_coord());
		return;
	}

	std::vector<Coord> cells = look_around(field);
	if (cells.empty())
	{
		return;
	}
	Coord moving_coord{ cells[rand() % cells.size()] };
	move(field, moving_coord);

}

void Herbivorous::breed(Creature_data& field)
{
	std::vector<Coord> cells = look_around(field);
	if(cells.empty())
	{
		return;
	}
	Coord breed_coord{ cells[rand()%cells.size()]};
	breed_one(field, breed_coord);
}

void Herbivorous::eat(Creature_data& field, std::shared_ptr <Creature> victim)
{
	ttl_ += std::dynamic_pointer_cast<Plant>(victim)->get_ttl_if_eaten();
	victim->set_ttl(0);
}

std::optional<std::shared_ptr<Creature>> Herbivorous::is_plant_here(Creature_data& field)
{
	const Cell& cell = field.get_field().get_cell(coord_);
	for (auto creature = cell.begin(); creature != cell.end(); ++creature)
	{
		if (!std::dynamic_pointer_cast<Plant>(*creature))
		{
			continue;
		}
		if ((*creature)->get_ttl() != 0) {
			return std::optional{ *creature };
		}
	}
	return {};
}

std::optional<std::shared_ptr<Creature>> Herbivorous::is_plant_near(Creature_data& field)
{
	std::vector<Coord> around_cells = look_around(field);
	std::vector<std::shared_ptr<Creature>> plants;
	for (auto cord : around_cells) {
		const Cell& cell = field.get_field().get_cell(cord);
		for (auto creature = cell.begin(); creature != cell.end(); ++creature)
		{
			if (!std::dynamic_pointer_cast<Plant>(*creature))
			{
				continue;
			}
			if ((*creature)->get_ttl() != 0) {
				plants.push_back(*creature);
			}
		}
	}
	if (plants.empty())
	{
		return {};
	}
	return std::optional{plants[rand() % plants.size()]};
}

std::optional<Coord> Herbivorous::is_predator_near(Creature_data& field)
{
	std::vector<Coord> around_cells = look_around(field);
	for (auto cord : around_cells) {
		const Cell& cell = field.get_field().get_cell(cord);
		for (auto creature = cell.begin(); creature != cell.end(); ++creature)
		{
			if (std::dynamic_pointer_cast<Predator>(*creature))
			{
				return std::optional<Coord>{(*creature)->get_coord()};
			}
		}
	}
	return {};
}

void Herbivorous::move(Creature_data& field, const Coord& coord)
{
	field.get_field().move_creature(coord, this);
}

bool Herbivorous::is_cell_is_suitable(Creature_data& data, const Coord& coord)
{
	return !!std::dynamic_pointer_cast<Ground>(data.get_field().get_cell(coord).get_landscape());
}

void Herbivorous::breed_one(Creature_data& data, const Coord& coord)
{
	std::shared_ptr<Creature> child = std::make_shared<Herbivorous>(ttl_ / 2, coord, tex_);
	ttl_ /= 2;
	data.get_list().push_back(child);
	data.get_field().add_creature(child);
}
