#include "Cell.h"
#include "Exceptions.h"

void Cell::add_creature(Creature& creature)
{
	creatures_.push_back(&creature);
	is_changed_ = true;
}


void Cell::remove_creature(const Creature& creature)
{
	auto it = std::ranges::find(creatures_, &creature);
	if(it == creatures_.end())
	{
			throw Bad_creature{};
	}
	creatures_.erase(it);

	is_changed_ = true;
}

bool Cell::is_empty() const
{
	return creatures_.empty();
}

LandScape& Cell::get_landscape() const
{
	return *landscape;
}

void Cell::set_landscape(LandScape& new_land)
{
	landscape = &new_land;
}
