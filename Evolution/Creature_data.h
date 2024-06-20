#pragma once

#include <istream>
#include <list>

#include "Cell.h"
#include "Coord.h"
#include "Creature_DTO.h"
#include "Landscape_DTO.h"
#include "TexturePack.h"
#include "Creature_parser.h"
#include "Landscape_pack.h"


class Cell;
class Creature;

class Creature_field final
{
public:
	Creature_field() :x_(0), y_(0) {}

	Creature_field(const Creature_field&) = delete;
	Creature_field(Creature_field&) = delete;
	Creature_field operator=(Creature_field&) = delete;
	Creature_field operator=( const Creature_field&) = delete;

	void set_size_of_field(const Coord&);

	Cell& get_cell(const Coord&);
	void add_creature(Creature&);
	void remove_creature(const Creature&);
	void move_creature(const Coord& end_coord, Creature&);

	size_t get_x() const { return x_; }
	size_t get_y() const { return y_; }
private:
	std::vector<Cell> field_;
	size_t x_, y_;

};


class Creature_list final
{
public:
	class Iterator
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;

		Iterator(std::list<Creature*>::const_iterator iter) : Creature_iter(iter) {}

		Creature& operator*() const { return **Creature_iter; }
		Iterator& operator++() { ++Creature_iter; return *this; }
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
		bool operator== (Iterator right) const { return Creature_iter == right.Creature_iter; }

	private:
		std::list<Creature*>::const_iterator Creature_iter;
	};
	Iterator begin() const { return Iterator{ list_.begin() }; }
	Iterator end() const { return Iterator{ list_.end() }; }

	Creature_list() = default;

	Creature_list(const Creature_list&) = delete;
	Creature_list(Creature_list&) = delete;
	Creature_list operator=(Creature_list&) = delete;
	Creature_list operator=(const Creature_list&) = delete;

	void remove_creature(const Creature&);
	void push_back(Creature&);
private:
	std::list<Creature*> list_;
};

class Creature_data
{
public:
	
	Creature_data(std::istream& creature_input, std::istream& landscape_input, const Texture_pack& textures, const Landscape_pack& landscapes);
	~Creature_data();

	Creature_data(Creature_data&) = delete;
	Creature_data(const Creature_data&) = delete;
	Creature_data operator=(Creature_data&) = delete;
	Creature_data operator=(const Creature_data&) = delete;

	Creature_list& get_list() { return list_; }
	Creature_field& get_field() { return field_; }
private:
	class Builder
	{
	public:
		Builder() = default;
		~Builder() = default;
		Builder& type(const std::string&);
		Builder& coordinate(const Coord&);
		Builder& ttl(size_t);
		Builder& texture(const Texture&);
		Creature* build();
		static Coord get_size_of_field(std::istringstream& input);
	private:
		std::string type_;
		Coord coord_;
		size_t ttl_;
		Texture texture_;
	};
	Creature_field field_;
	Creature_list list_;
};