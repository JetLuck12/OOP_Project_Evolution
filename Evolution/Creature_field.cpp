#include "Creature_data.h"

#include "Cell.h"
#include "Exceptions.h"

void Creature_field::set_size_of_field(const Coord& coord)
{
	if (x_ != 0)
	{
		throw Double_resize{};
	}
	x_ = coord.get_x();
	y_ = coord.get_y();
	field_.resize(x_ * y_);
}

void Creature_field::add_creature(std::shared_ptr <Creature> creature)
{
	if (creature->get_coord().get_x() > x_ || creature->get_coord().get_y() > y_)
	{
		throw Wrong_coords{};
	}
	field_[creature->get_coord().get_y() * x_ + creature->get_coord().get_x()].add_creature(creature);
}

Cell& Creature_field::get_cell(const Coord& coord)
{
	if (coord.get_x() > x_ || coord.get_y() > y_)
	{
		throw Wrong_coords{};
	}
	return field_[coord.get_y() * x_ + coord.get_x()];
}

void Creature_field::move_creature(const Coord& end_coord, Creature* creature)
{
	if (end_coord.get_x() > x_ || end_coord.get_y() > y_)
	{
		throw Wrong_coords{};
	}
	std::shared_ptr<Creature> creature_ptr = get_cell(creature->get_coord()).find_creature(creature);
	remove_creature(creature_ptr);
	creature_ptr->set_coord(end_coord);
	field_[end_coord.get_y() * x_ + end_coord.get_x()].add_creature(creature_ptr);

}

void Creature_field::remove_creature(std::shared_ptr <Creature> creature)
{
	if (creature->get_coord().get_x() > x_ || creature->get_coord().get_y() > y_)
	{
		throw Wrong_coords{};
	}
	field_[creature->get_coord().get_y() * x_ + creature->get_coord().get_x()].remove_creature(creature);
}

