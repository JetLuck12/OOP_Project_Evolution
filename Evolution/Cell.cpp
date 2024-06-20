#include "Cell.h"
#include <algorithm>
#include "Exceptions.h"

void Cell::set_landscape(std::shared_ptr<Landscape> new_land)
{
	landscape = new_land;
}

void Cell::add_creature(std::shared_ptr <Creature> creature)
{
	is_changed_ = true;
	creatures_.push_back(creature);
}

std::shared_ptr<Creature>& Cell::find_creature(Creature* creature)
{
	for (auto& creature_ptr : creatures_)
	{
		if (creature_ptr.get() == creature)
		{
			return creature_ptr;
		}
	}
	throw Unfound_creature{};
}


std::shared_ptr<Landscape> Cell::get_landscape() const
{
	return landscape;
}

bool Cell::is_empty() const
{
	return creatures_.empty();
}

void Cell::remove_creature(const std::shared_ptr <Creature>& creature)
{
	is_changed_ = true;
	auto creature_iter = std::ranges::find(creatures_, creature);
	if(creature_iter == creatures_.end())
	{
		throw Unfound_creature{};
	}
	creatures_.erase(creature_iter);
}

