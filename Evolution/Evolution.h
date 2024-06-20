#pragma once

#include <istream>

#include "TexturePack.h"
#include "Creature_data.h"
#include "Plant.h"
#include "Predator.h"
#include "Herbivorous.h"
#include "Goat.h"
#include "Cell.h"
#include "Ground.h"


class Evolution final
{
public:
	Evolution(std::istream& creature_input, std::istream& landscape_input,const Texture_pack& textures, const Landscape_pack& landscapes);
	void update(std::ostream&);
private:
	Creature_data data_;
	size_t tick;
	void remove_died();
	void process_actions();
	void draw(std::ostream&);
};