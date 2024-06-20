#include "Wolf.h"
#include "Meadow.h"
#include "Creature_data.h"

bool Wolf::is_cell_is_suitable(Creature_data& data, const Coord& coord)
{
	return dynamic_cast<Meadow*>(&data.get_field().get_cell(coord).get_landscape());
}

void Wolf::breed_one(Creature_data& data, const Coord& coord)
{
	Wolf* child = new  Wolf(ttl_ / 2, coord, tex_);
	ttl_ /= 2;
	data.get_list().push_back(*child);
	data.get_field().add_creature(*child);
}

std::optional<Creature*> Wolf::is_enemy_near(Creature_data& field)
{
	auto cells = look_around(field);
	for (auto cell : cells)
	{
		for (auto creature = field.get_field().get_cell(cell).begin(); creature != field.get_field().get_cell(cell).end(); ++creature)
		{
			if (!dynamic_cast<Predator*>(&*creature))
			{
				continue;
			}
			if (!dynamic_cast<Wolf*>(&*creature))
			{
				return std::optional<Creature*>{&*creature};
			}
		}
	}
	return {};
}
