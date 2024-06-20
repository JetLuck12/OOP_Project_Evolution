#include <map>
#include "Evolution.h"

#include "Processing.h"


Evolution::Evolution(std::istream& input, std::istream& landscape_input, const Texture_pack& textures, const Landscape_pack& landscapes) : data_(input, landscape_input, textures, landscapes)
{
	init_draw(data_);
	tick = 0;
}

void Evolution::draw(std::ostream& output)
{
	Creature_field& field = data_.get_field();
	output << "#########################################################\n";
	for (size_t i = 0; i < field.get_y(); ++i)
	{
		output << "#";
		for (size_t j = 0; j < field.get_x(); ++j)
		{

			if(field.get_cell(Coord{ j, i, 0 }).begin() == field.get_cell(Coord{ j, i, 0 }).end())
			{
				output << std::string{ "  " };
			}
			else {
				auto creature = --field.get_cell(Coord{ j, i, 0 }).end();
				output <<  (*creature).get_texture().get_texture()  << std::string{ " " };
			}
		}
		output << std::string{ "#\n" };
	}
	output << "#########################################################\n";
	size_t plants = 0, herbs = 0, preds = 0;
	for(auto creature = data_.get_list().begin(); creature != data_.get_list().end(); ++creature)
	{
		if(dynamic_cast<Plant*>(&*creature))
		{
			plants++;
		}
		else if(dynamic_cast<Herbivorous*>(&*creature))
		{
			herbs++;
		}
		else if(dynamic_cast<Predator*>(&*creature))
		{
			preds++;
		}
	}
	output << "Plants: " << plants << '\n';
	output << "Herbivirouses: " << herbs << '\n';
	output << "Predators: " << preds << '\n';
}

void Evolution::process_actions()
{
	for (auto creature = data_.get_list().begin(); creature != data_.get_list().end(); ++creature)
	{
		if ((*creature).get_ttl() != 0) {
			(*creature).action(data_);
			(*creature).reduce_ttl();
		}
	}
	tick++;
}

void Evolution::remove_died()
{
	std::vector<Creature*> died_creatures;
	for (auto creature = data_.get_list().begin(); creature != data_.get_list().end(); ++creature)
	{
		if ((*creature).get_ttl() == 0)
		{
			died_creatures.push_back(&*creature);

		}
	}
	for (auto x : died_creatures)
	{
		data_.get_field().remove_creature(*x);
		data_.get_list().remove_creature(*x);
		delete x;
	}
}

void Evolution::update(std::ostream& output)
{
	erase_creatures(data_);
	remove_died();
	process_actions();
	processing_draw(data_, tick);
	//draw(output);
}

