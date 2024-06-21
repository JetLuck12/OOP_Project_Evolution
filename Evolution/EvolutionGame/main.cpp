
#include "Evolution.h"
#include "Processing.h"
#include "Creature_configuration.h"

#include <sstream>
#include <chrono>
#include <windows.h>
#include <fstream>
#include <memory>

#include "Meadow.h"
#include "Mountains.h"
#include "Water.h"

int main()
{
	{
		srand(std::chrono::system_clock::now().time_since_epoch().count());
		std::ifstream input("Creatures2.txt");

		std::ifstream landscape_stream( "Landscape2.txt" );

		Texture_pack creature_textures{};
		creature_textures.add_texture("Grass", Texture{ CHAR_GRASS });
		creature_textures.add_texture("Moss", Texture{ CHAR_MOSS });
		creature_textures.add_texture("Deer", Texture{ CHAR_DEER });
		creature_textures.add_texture("Goat", Texture{ CHAR_GOAT });
		creature_textures.add_texture("Wolf", Texture{ CHAR_WOLF });
		creature_textures.add_texture("Lynx", Texture{ CHAR_LYNX });

		Landscape_pack landscapes{};
		landscapes.add_texture("Meadow", new Meadow(COLOR_MEADOW));
		landscapes.add_texture("Mountain", new Mountains(COLOR_MOUNTAINS));
		landscapes.add_texture("Water", new Water(COLOR_WATER));

		Evolution evo(input, landscape_stream, creature_textures, landscapes);
		size_t tick = 0;
		while (true)
		{
			tick++;
			std::ostringstream output;
			Sleep(200);
			evo.update(output);
		}
	}
}

