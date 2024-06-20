#include "Creature_data.h"
#include "Creature.h"
#include "Landscape_parser.h"

Creature_data::Creature_data(std::istream& creature_input, std::istream& landscape_input, const Texture_pack& textures, const Landscape_pack& landscapes)
{

	std::string string_line;
	std::getline(creature_input, string_line);
	std::istringstream stream_line(string_line);
	field_.set_size_of_field(Builder::get_size_of_field(stream_line));
	Builder builder{};
	while (std::getline(creature_input, string_line))
	{
		std::istringstream stream_line(string_line);
		Creature_DTO raw_creature = Creature_parser::get_next(stream_line);
		if (raw_creature.get_x() < 0 ||
			raw_creature.get_x() >= field_.get_x() ||
			raw_creature.get_y() < 0 ||
			raw_creature.get_y() >= field_.get_y() ||
			raw_creature.get_z() < 0 ||
			raw_creature.get_ttl() < 0)
		{
			throw Bad_numbers{};
		}


		Creature* child = builder
			.type(raw_creature.get_type())
			.texture(textures.get_texture(raw_creature.get_type()))
			.ttl(raw_creature.get_ttl())
			.coordinate(Coord{
				static_cast<size_t>(raw_creature.get_x()),
				static_cast<size_t>(raw_creature.get_y()),static_cast<size_t>(raw_creature.get_z())
				})
			.build();

		field_.add_creature(*child);
		list_.push_back(*child);
	}
	while (std::getline(landscape_input, string_line))
	{
		std::istringstream stream_line(string_line);
		Landscape_DTO raw_landscape = Landscape_parser::get_next(stream_line);
		if (raw_landscape.get_x() < 0 ||
			raw_landscape.get_x() >= field_.get_x() ||
			raw_landscape.get_y() < 0 ||
			raw_landscape.get_y() >= field_.get_y())
		{
			throw Bad_numbers{};
		}
		field_.get_cell(
			Coord{
				static_cast<size_t>(raw_landscape.get_x()) ,
				static_cast<size_t>(raw_landscape.get_y()),
				0 }).set_landscape(*landscapes.get_texture(raw_landscape.get_type()));
	}
	for (size_t y = 0; y < field_.get_y(); ++y)
	{
		for (size_t x = 0; x < field_.get_x(); ++x)
		{
			if (!field_.get_cell(Coord{x,y,0}).is_land_init())
			{
				throw few_lands_exc{};
			}
		}
	}
}


Creature_data::~Creature_data()
{
	auto x = list_.begin();
	while (x != list_.end())
	{
		Creature& creature = *x;
		field_.remove_creature(creature);
		list_.remove_creature(creature);
		delete& creature;
		x = list_.begin();
	}
}

