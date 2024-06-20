#pragma once

class Coord final
{
public:
	Coord() :x_(0), y_(0), z_(0){}
	Coord(size_t x, size_t y, size_t z) :x_(x), y_(y), z_(z)  {}
	bool operator==(const Coord&) const;
	bool operator==(Coord& right) const;
	Coord& operator=(const Coord& new_coord) = default;
	bool in_one_place(const Coord&) const;
	Coord operator*(size_t) const;
	Coord operator+(const Coord& right) const;
	Coord operator-(const Coord& right) const;
	size_t get_x() const;
	size_t get_y() const;
	size_t get_z() const;
private:
	size_t x_;
	size_t y_;
	size_t z_;
};