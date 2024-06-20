#include "Moss.h"

#include "Mountains.h"

bool Moss::is_cell_is_suitable(Creature_data& data, const Coord& coord)
{
	return dynamic_cast<Mountains*>(&data.get_field().get_cell(coord).get_landscape());
}

void Moss::breed_one(Creature_data& field, const Coord& coord)
{
	Moss* child = new Moss(1, coord, tex_);
	field.get_list().push_back(*child);
	field.get_field().add_creature(*child);
}

bool Moss::is_breedable() const
{
	return time_after_multiply >= breeding_period;
}
