#pragma once
#include <vector>
#include "Creature.h"
#include "Landscape.h"

class Creature;

class Cell final
{
public:
	class Iterator
	{
	public:
		using iterator_category = std::forward_iterator_tag;

		Iterator(std::vector<Creature*>::const_iterator ptr) : Creature_ptr(ptr) {}
		Creature& operator*() const { return **Creature_ptr; }
		Iterator& operator++() { ++Creature_ptr; return *this; }
		Iterator& operator--() { --Creature_ptr; return *this; }
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
		bool operator== (const Iterator& b) const { return Creature_ptr == b.Creature_ptr; }
		bool operator!= ( const Iterator& b) const { return Creature_ptr != b.Creature_ptr; }

	private:
		std::vector<Creature*>::const_iterator Creature_ptr;
	};
	Iterator begin() const { return Iterator{creatures_.begin()}; }
	Iterator end() const { return Iterator{ creatures_.end() }; }
	Cell() { landscape = nullptr; is_changed_ = false; }
	void add_creature(Creature&);
	void remove_creature(const Creature&);
	bool is_empty() const;
	LandScape& get_landscape() const;
	void set_landscape(LandScape& new_land);
	bool is_changed() const { return is_changed_; }
	void reset_change() { is_changed_ = false; }
	bool is_land_init() const { return landscape; }
private:
	std::vector<Creature*> creatures_;
	LandScape* landscape;
	bool is_changed_;
};