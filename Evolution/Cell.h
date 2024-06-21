#pragma once
#include <memory>
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

		Iterator(std::vector<std::shared_ptr<Creature>>::const_iterator ptr) : Creature_ptr(ptr) {}
		const std::shared_ptr<Creature>& operator*() const { return *Creature_ptr; }
		
		Iterator& operator++() { ++Creature_ptr; return *this; }
		Iterator& operator--() { --Creature_ptr; return *this; }
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
		bool operator== (const Iterator& b) const { return Creature_ptr == b.Creature_ptr; }
		bool operator!= ( const Iterator& b) const { return Creature_ptr != b.Creature_ptr; }

	private:
		std::vector<std::shared_ptr<Creature>>::const_iterator Creature_ptr;
	};
	Iterator begin() const { return Iterator{creatures_.begin()}; }
	Iterator end() const { return Iterator{ creatures_.end() }; }
	Cell() { landscape = nullptr; is_changed_ = false; }
	void add_creature(std::shared_ptr<Creature>);
	void remove_creature(std::shared_ptr <Creature>);
	std::shared_ptr<Creature>& find_creature(Creature*);
	bool is_empty() const;
	std::shared_ptr<Landscape> get_landscape() const;
	void set_landscape(std::shared_ptr<Landscape> new_land);
	bool is_changed() const { return is_changed_; }
	void reset_change() { is_changed_ = false; }
	bool is_land_init() const { return !!landscape; }
private:
	std::vector<std::shared_ptr<Creature>> creatures_;
	std::shared_ptr <Landscape> landscape;
	bool is_changed_;
};