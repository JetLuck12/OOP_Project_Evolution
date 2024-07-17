#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include "Animation.h"
#include "Action_animation_list.h"

#include "Coord.h"

class Creature_data;

class Creature
{
public:
	Creature(size_t ttl, const Coord& coord, std::shared_ptr<Animation> tex):ttl_(ttl), coord_(coord),animation_(tex) {}
	virtual ~Creature() = default;
	size_t get_ttl() const;
	void set_ttl(size_t new_ttl);
	const Coord& get_coord() const;
	void set_coord(const Coord& new_coord);
	std::shared_ptr<Animation> get_texture() const;
	virtual void action(Creature_data& field) = 0;
	virtual void reduce_ttl();
protected:
	virtual std::vector<Coord> look_around(Creature_data& field);
	virtual bool is_cell_is_suitable(Creature_data& data, const Coord& coord) = 0;
	size_t ttl_;
	Coord coord_;
	std::shared_ptr<Animation> animation_;
	Animations_list animations_list_;
	std::string action_;
};
