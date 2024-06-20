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

std::shared_ptr<Creature> Creature_data::Builder::build()
{

	if (type_ == "Deer") {
		return std::make_shared<Deer>(ttl_, coord_, texture_);
	}
	if (type_ == "Goat") {
		return std::make_shared<Goat>(ttl_, coord_, texture_);
	}
	if (type_ == "Moss")
	{
		return std::make_shared<Moss>(ttl_, coord_, texture_);
	}
	if (type_ == "Wolf")
	{
		return std::make_shared <Wolf>(ttl_, coord_, texture_);
	}
	if (type_ == "Grass")
	{
		return std::make_shared <Grass>(ttl_, coord_, texture_);
	}
	if (type_ == "Lynx")
	{
		return std::make_shared <Lynx>(ttl_, coord_, texture_);
	}
		throw Builder_exc{};
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
