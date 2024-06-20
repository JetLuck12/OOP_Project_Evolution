#include "Creature.h"

size_t Creature::get_ttl() const
{
	return ttl_;
}

void Creature::set_ttl(size_t new_ttl)
{
	ttl_ = new_ttl;
}

const Coord& Creature::get_coord() const
{
	return coord_;
}

void Creature::reduce_ttl()
{
	ttl_ -= 1;
}

const Texture& Creature::get_texture() const
{
	return tex_;
}

void Creature::set_coord(const Coord& new_coord)
{
	coord_ = new_coord;
}

std::vector<Coord> Creature::look_around(Creature_data& field)
{
	std::vector<Coord> vec;
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			size_t x = (coord_.get_x() + field.get_field().get_x() + j)%field.get_field().get_x();
			size_t y = (coord_.get_y() + field.get_field().get_y() + i)%field.get_field().get_y();
			Coord coord{ x, y, coord_.get_z() };
			if (is_cell_is_suitable(field, coord))
			{
				vec.push_back(coord);
			}

		}
	}
	return vec;
}
