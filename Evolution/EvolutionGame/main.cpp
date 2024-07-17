#include <include/SFML/Graphics.hpp>
#include "Evolution.h"
#include <sstream>
#include <chrono>
#include <windows.h>
#include <fstream>
#include <memory>
#include <memory>
#include "Texture_init.h"
#include "SFML_drawing.h"
#include <sstream>

#include "Dragging.h"
#include "Meadow.h"


int main()
{
	{
		srand(std::chrono::system_clock::now().time_since_epoch().count());
		std::ifstream input("Creatures.txt");

		std::ifstream landscape_stream( "Landscape.txt" );

        Texture_pack creature_textures = texture_init();

        Landscape_pack landscapes = landscape_init();

        sf::RenderWindow window;
        window.create(sf::VideoMode(1920, 1080), "My window", sf::Style::Close);
        window.setVerticalSyncEnabled(true);

        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;

        sf::View game(sf::Vector2f(860, 540), sf::Vector2f(1720, 1080));
        game.setViewport(sf::FloatRect{ 0,0,0.8f,1 });

        sf::View legend(sf::Vector2f(960, 540), sf::Vector2f(200, 1080));
        legend.setViewport(sf::FloatRect{ 0.8f,0,0.2f,1 });


		Evolution evo(input, landscape_stream, creature_textures, landscapes);
		size_t tick = 0;
        ViewDragger view_dragger{ window };

        while (window.isOpen())
        {
            //mPos = sf::Mouse::getPosition(window);
            sf::Event event;
            
            while (window.pollEvent(event))
            {
                view_dragger.handleEvent(event, game);
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::MouseWheelScrolled)
                {
                    if (event.mouseWheelScroll.delta < 0)
                    {
                        //game.zoom(1.024f);
                        game.zoom(1.25f);
                    }
                    else
                    {
                        //game.zoom(0.9765625f);
                        game.zoom(0.8f);
                    }
                }
            }
            std::iostream output(nullptr);
            //Sleep(200);
            window.clear(sf::Color::Black);

        	evo.update(window, game, legend);

            
            window.display();








        }

	}
}

