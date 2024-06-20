#pragma once

#include "Creature_field.h"

class Creature_Mediator
{
public:
	Creature_Mediator(const std::shared_ptr<Creature_field>& field):field_(field){}
	const std::array<std::shared_ptr<Creature>, 9>& look_around();
private:
	std::shared_ptr<Creature_field> field_;
};