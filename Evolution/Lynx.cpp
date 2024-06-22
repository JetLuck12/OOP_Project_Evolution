#include "Lynx.h"

#include <memory>

#include "Meadow.h"
#include "Water.h"

#include "Creature_data.h"

void Lynx::breed_one(Creature_data& data, const Coord& coord)
{
	std::shared_ptr<Creature> child = std::make_shared<Lynx>(ttl_ / 2, coord, tex_);
	ttl_ /= 2;
	data.get_list().push_back(child);
	data.get_field().add_creature(child);
}

bool Lynx::is_cell_is_suitable(Creature_data& data, const Coord& coord)
{
	return !std::dynamic_pointer_cast<Water>(data.get_field().get_cell(coord).get_landscape());
}

std::optional<std::shared_ptr<Creature>> Lynx::is_enemy_near(Creature_data& field)
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
			if (!std::dynamic_pointer_cast<Lynx>(*creature))
			{
				return std::optional<std::shared_ptr<Creature>>{*creature};
			}
		}
	}
	return {};
}
