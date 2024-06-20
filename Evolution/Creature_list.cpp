#include "Creature_data.h"

void Creature_list::push_back(Creature& creature)
{
	list_.push_back(&creature);
}

void Creature_list::remove_creature(const Creature& creature)
{
	auto creature_iter = std::ranges::find(list_, &creature);
	if (creature_iter == list_.end())
	{
		throw Unfound_creature{};
	}
	list_.erase(creature_iter);
}

