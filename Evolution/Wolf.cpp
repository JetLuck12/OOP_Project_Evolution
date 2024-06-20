#include "Wolf.h"

#include <memory>

#include "Meadow.h"
#include "Creature_data.h"

bool Wolf::is_cell_is_suitable(Creature_data& data, const Coord& coord)
{
	return !!std::dynamic_pointer_cast<std::shared_ptr<Meadow>>(data.get_field().get_cell(coord).get_landscape());
}

void Wolf::breed_one(Creature_data& data, const Coord& coord)
{
	std::shared_ptr<Creature> child = std::make_shared<Wolf>(ttl_ / 2, coord, tex_);
	ttl_ /= 2;
	data.get_list().push_back(child);
	data.get_field().add_creature(child);
}

std::optional<std::shared_ptr<Creature>> Wolf::is_enemy_near(Creature_data& field)
{
	auto cells = look_around(field);
	for (auto cell : cells)
	{
		for (auto creature = field.get_field().get_cell(cell).begin(); creature != field.get_field().get_cell(cell).end(); ++creature)
		{
			if (!std::dynamic_pointer_cast<Predator>(*creature))
			{
				continue;
			}
			if (!std::dynamic_pointer_cast<Wolf>(*creature))
			{
				return std::optional<std::shared_ptr<Creature>>{*creature};
			}
		}
	}
	return {};
}
