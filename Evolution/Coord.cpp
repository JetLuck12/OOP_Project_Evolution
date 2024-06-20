#include "Coord.h"

size_t Coord::get_x() const
{
	return x_;
}

size_t Coord::get_y() const
{
	return y_;
}

size_t Coord::get_z() const
{
	return z_;
}


bool Coord::operator==(const Coord& right) const
{
	return x_ == right.x_ && y_ == right.y_ && z_ == right.get_z();
}

bool Coord::operator==(Coord& right) const
{
	return x_ == right.x_ && y_ == right.y_ && z_ == right.get_z();
}

Coord Coord::operator+(const Coord& right) const
{
	return Coord{ this->x_ + right.x_, this->y_ + right.y_ , z_ + right.z_};
}

Coord Coord::operator-(const Coord& right) const
{
	return Coord{ this->x_ - right.x_, this->y_ - right.y_ , z_ + right.z_};
}

Coord Coord::operator*(size_t num) const
{
	return Coord{ x_ * num, y_ * num, z_ * num };
}

bool Coord::in_one_place(const Coord& right) const
{
	return x_ == right.x_ && y_ == right.y_;
}