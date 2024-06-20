#include "Moss.h"

#include <memory>

#include "Creature_data.h"
#include "Mountains.h"

bool Moss::is_cell_is_suitable(Creature_data& data, const Coord& coord)
{
	return !!std::dynamic_pointer_cast<Mountains>(data.get_field().get_cell(coord).get_landscape());
}

void Moss::breed_one(Creature_data& field, const Coord& coord)
{
	std::shared_ptr<Creature> child = std::make_shared<Moss>(1, coord, tex_);
	field.get_list().push_back(child);
	field.get_field().add_creature(child);
}

bool Moss::is_breedable() const
{
	return time_after_multiply >= breeding_period;
}
