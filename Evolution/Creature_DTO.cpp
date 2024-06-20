#include "Creature_DTO.h"

const std::string& Creature_DTO::get_type() const
{
	return type_;
}

int Creature_DTO::get_x() const
{
	return x_;
}

int Creature_DTO::get_y() const
{
	return y_;
}

int Creature_DTO::get_z() const
{
	return z_;
}

int Creature_DTO::get_ttl() const
{
	return ttl_;
}
