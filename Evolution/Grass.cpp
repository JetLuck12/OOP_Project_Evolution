#include "Grass.h"

#include "Meadow.h"

bool Grass::is_cell_is_suitable(Creature_data& data, const Coord& coord)
{
	return dynamic_cast<Meadow*>(&data.get_field().get_cell(coord).get_landscape());
}

void Grass::breed_one(Creature_data& field, const Coord& coord)
{
	Grass* child = new Grass(1, coord, tex_);
	field.get_list().push_back(*child);
	field.get_field().add_creature(*child);
}
