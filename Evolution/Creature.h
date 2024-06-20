#pragma once
#include <vector>

#include "Texture.h"
#include "Coord.h"

class Creature_data;

class Creature
{
public:
	Creature(size_t ttl, const Coord& coord, Texture tex):ttl_(ttl), coord_(coord), tex_(tex){}
	virtual ~Creature() = default;
	size_t get_ttl() const;
	void set_ttl(size_t new_ttl);
	const Coord& get_coord() const;
	void set_coord(const Coord& new_coord);
	const Texture& get_texture() const;
	virtual void action(Creature_data& field) = 0;
	virtual void reduce_ttl();
protected:
	virtual std::vector<Coord> look_around(Creature_data& field);
	virtual bool is_cell_is_suitable(Creature_data& data, const Coord& coord) = 0;
	size_t ttl_;
	Coord coord_;
	Texture tex_;
};
