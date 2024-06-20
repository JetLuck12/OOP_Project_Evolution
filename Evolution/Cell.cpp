#include "Cell.h"

#include "Exceptions.h"

void Cell::set_landscape(LandScape& new_land)
{
	landscape = &new_land;
}

void Cell::add_creature(Creature& creature)
{
	creatures_.push_back(&creature);
}

LandScape& Cell::get_landscape() const
{
	return *landscape;
}

bool Cell::is_empty() const
{
	return creatures_.empty();
}

void Cell::remove_creature(const Creature& creature)
{
	auto creature_iter = std::ranges::find(creatures_, &creature);
	if(creature_iter == creatures_.end())
	{
		throw Unfound_creature{};
	}
	creatures_.erase(creature_iter);
}

