#include "Goat.h"

#include <memory>

#include "Creature_data.h"

void Goat::breed_one(Creature_data& data, const Coord& coord)
{
	std::shared_ptr<Creature> child = std::make_shared<Goat>(ttl_ / 2, coord, tex_);
	ttl_ /= 2;
	data.get_list().push_back(child);
	data.get_field().add_creature(child);
}
