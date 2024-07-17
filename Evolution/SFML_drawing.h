#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "TexturePack.h"

void draw_entities(sf::RenderWindow& window, std::iostream& stream, Texture_pack& textures);
void draw_legend(sf::RenderWindow& window, std::iostream& stream);