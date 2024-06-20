#include "Plant.h"

#include <memory>

#include "Creature_data.h"
#include "Cell.h"
#include "Ground.h"

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
		std::shared_ptr<Creature> creature = *creature_it;
		if (std::dynamic_pointer_cast<std::shared_ptr <Plant>>(creature))
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
	return !!std::dynamic_pointer_cast<Ground>(data.get_field().get_cell(coord).get_landscape());
	
}
