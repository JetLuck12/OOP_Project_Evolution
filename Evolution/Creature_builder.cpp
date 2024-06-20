#include "Creature_data.h"

#include <string>
#include <sstream>

#include "Deer.h"
#include "Plant.h"
#include "Predator.h"
#include "Exceptions.h"
#include "Goat.h"
#include "Grass.h"
#include "Lynx.h"
#include "Moss.h"
#include "Processing.h"
#include "Wolf.h"



Coord Creature_data::Builder::get_size_of_field(std::istringstream& input)
{
	int x = 0, y = 0;
	input >> x >> y;
	if (x <= 0 || y <= 0) {
		throw Wrong_size_exc{};
	}
	return Coord{ static_cast<size_t>(x),static_cast<size_t>(y),0 };
}

Creature* Creature_data::Builder::build()
{
	Creature* child;
	if (type_ == "Deer") {
		child = new Deer(ttl_, coord_, texture_);
	}
	else if (type_ == "Goat") {
		child = new Goat(ttl_, coord_, texture_);
	}
	else if (type_ == "Moss")
	{
		child = new Moss(ttl_, coord_, texture_);
	}
	else if (type_ == "Wolf")
	{
		child = new Wolf(ttl_, coord_, texture_);
	}
	else if (type_ == "Grass")
	{
		child = new Grass(ttl_, coord_, texture_);
	}
	else if (type_ == "Lynx")
	{
		child = new Lynx(ttl_, coord_, texture_);
	}
	else
	{
		throw Builder_exc{};
	}
	if(child == nullptr)
	{
		throw memory_problems{};
	}
	return child;
}

Creature_data::Builder& Creature_data::Builder::coordinate(const Coord& coord)
{
	coord_ = coord;
	return *this;
}

Creature_data::Builder& Creature_data::Builder::texture(const Texture& tex)
{
	texture_ = tex;
	return *this;
}

Creature_data::Builder& Creature_data::Builder::ttl(size_t ttl)
{
	ttl_ = ttl;
	return *this;
}

Creature_data::Builder& Creature_data::Builder::type(const std::string& type)
{
	type_ = type;
	return *this;
}
