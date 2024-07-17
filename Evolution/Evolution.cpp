#include <map>
#include "Evolution.h"

#define TILE_SIZE_X 10.
#define TILE_SIZE_Y 10.

Evolution::Evolution(std::istream& input, std::istream& landscape_input, const Texture_pack& textures, const Landscape_pack& landscapes) : data_(input, landscape_input, textures, landscapes)
{
	tick = 0;
}

void Evolution::draw(sf::RenderWindow& window, sf::View& game, sf::View& legend)
{
	window.setView(game);
	Creature_field& field = data_.get_field();
	for (size_t i = 0; i < field.get_y(); ++i)
	{
		for (size_t j = 0; j < field.get_x(); ++j)
		{
			sf::Sprite shape(*field.get_cell(Coord{ j, i, 0 }).get_landscape()->get_texture());
			shape.setPosition(j * 10, i * 10);
			//float magni_x = float(10) / field.get_cell(Coord{ j, i, 0 }).get_landscape()->get_texture()->getSize().x;
			shape.setScale(TILE_SIZE_X / field.get_cell(Coord{ j, i, 0 }).get_landscape()->get_texture()->getSize().x, TILE_SIZE_Y / field.get_cell(Coord{ j, i, 0 }).get_landscape()->get_texture()->getSize().y );
			window.draw(shape);
			if(field.get_cell(Coord{ j, i, 0 }).begin() != field.get_cell(Coord{ j, i, 0 }).end())
			{
				auto creature = --field.get_cell(Coord{ j, i, 0 }).end();
				sf::Sprite creature_shape(*(*creature)->get_texture());
				creature_shape.setPosition(j * 10, i * 10);
				creature_shape.setScale(TILE_SIZE_X / (*creature)->get_texture()->getSize().x, TILE_SIZE_Y / (*creature)->get_texture()->getSize().y);
				
				window.draw(creature_shape);
			}
		}
	}
	size_t plants = 0, herbs = 0, preds = 0;
	for(auto creature = data_.get_list().begin(); creature != data_.get_list().end(); ++creature)
	{
		if(std::dynamic_pointer_cast<Plant>(*creature))
		{
			plants++;
		}
		else if(std::dynamic_pointer_cast<Herbivorous>(*creature))
		{
			herbs++;
		}
		else if(std::dynamic_pointer_cast<Predator>(*creature))
		{
			preds++;
		}
	}
	std::string output;
	output += "Plants: ";
	output += std::to_string(plants);
	output += '\n';
	output += "Herbivirouses: ";
	output += std::to_string(herbs);
	output += '\n';
	output += "Predators: ";
	output += std::to_string(preds);
	output += "\n";

	sf::Font font;
	if (!font.loadFromFile("fonts/times.ttf"))
	{
		throw std::invalid_argument{ "bad font" };
	}

	sf::Text legend_text;
	legend_text.setCharacterSize(20);
	legend_text.setFillColor(sf::Color::White);
	legend_text.setFont(font);
	legend_text.setString(output);
	legend_text.setPosition(900, 0);
	window.setView(legend);
	window.draw(legend_text);

}

void Evolution::process_actions()
{
	for (auto creature = data_.get_list().begin(); creature != data_.get_list().end(); ++creature)
	{
		if ((*creature)->get_ttl() != 0) {
			(*creature)->action(data_);
			(*creature)->reduce_ttl();
		}
	}
	tick++;
}

void Evolution::remove_died()
{
	std::vector<std::shared_ptr<Creature>> died_creatures;
	for (auto creature = data_.get_list().begin(); creature != data_.get_list().end(); ++creature)
	{
		if ((*creature)->get_ttl() == 0)
		{
			died_creatures.push_back(*creature);

		}
	}
	for (const auto& x : died_creatures)
	{
		data_.get_field().remove_creature(x);
		data_.get_list().remove_creature(x);
	}
}

void Evolution::update(sf::RenderWindow& window, sf::View& game, sf::View& legend)
{
	//erase_creatures(data_);
	if (std::chrono::system_clock::now() - last_time_update > std::chrono::milliseconds{ 200 })
	{
		remove_died();
		process_actions();
		last_time_update = std::chrono::system_clock::now();
	}
	//processing_draw(data_, tick);
	draw(window, game, legend);
}

