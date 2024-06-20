#include "Deer.h"

#include <memory>

#include "Creature_data.h"
#include "Meadow.h"

bool Deer::is_cell_is_suitable(Creature_data& data, const Coord& coord)
{
	return !!std::dynamic_pointer_cast<Meadow>(data.get_field().get_cell(coord).get_landscape());
}

void Deer::breed_one(Creature_data& data, const Coord& coord)
{
	std::shared_ptr <Creature> child = std::make_shared<Deer>(ttl_ / 2, coord, tex_);
	ttl_ /= 2;
	data.get_list().push_back(child);
	data.get_field().add_creature(child);
}
