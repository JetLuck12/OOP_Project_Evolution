#include "Lynx.h"

#include "Meadow.h"
#include "Water.h"

void Lynx::breed_one(Creature_data& data, const Coord& coord)
{
	Lynx* child = new  Lynx(ttl_ / 2, coord, tex_);
	ttl_ /= 2;
	data.get_list().push_back(*child);
	data.get_field().add_creature(*child);
}

bool Lynx::is_cell_is_suitable(Creature_data& data, const Coord& coord)
{
	return !dynamic_cast<Water*>(&data.get_field().get_cell(coord).get_landscape());
}

std::optional<Creature*> Lynx::is_enemy_near(Creature_data& field)
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
			if (!dynamic_cast<Lynx*>(&*creature))
			{
				return std::optional<Creature*>{&*creature};
			}
		}
	}
	return {};
}
