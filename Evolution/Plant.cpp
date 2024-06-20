#include "Plant.h"
#include "Creature_data.h"
#include "Cell.h"
#include "Ground.h"

class Cell;
class Creature_data;

void Plant::action(Creature_data& field)
{
	if (is_breedable())
	{
		time_after_multiply = 0;
		breed_around(field);
	}
	else
	{
		time_after_multiply++;
	}
}

bool Plant::is_plant_here(const Cell& cell)
{
	for (auto creature_it = cell.begin(); creature_it != cell.end(); ++creature_it)
	{
		const Creature* creature = &*creature_it;
		if (dynamic_cast<const Plant*>(creature))
		{
			return true;
		}
	}
	return false;
}


void Plant::breed_around(Creature_data& field)
{
	std::vector<Coord> cells = look_around(field);
	for (auto cell : cells) {
		if (!is_plant_here(field.get_field().get_cell(cell)))
		{
			breed_one(field, cell);
		}
	}
}


bool Plant::is_cell_is_suitable(Creature_data& data, const Coord& coord)
{
	return dynamic_cast<Ground*>(&data.get_field().get_cell(coord).get_landscape());
	
}

void Plant::breed_one(Creature_data& field, const Coord& coord)
{
	Plant* child = new Plant(1, coord, tex_);
	field.get_list().push_back(*child);
	field.get_field().add_creature(*child);
}

bool Plant::is_breedable() const
{
	return time_after_multiply >= breeding_period;
}
