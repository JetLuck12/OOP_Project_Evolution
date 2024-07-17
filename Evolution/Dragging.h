#pragma once

#include <SFML/Graphics.hpp>
class ViewDragger
{
private:
    sf::RenderTarget& RTwindow;
    sf::Vector2i previousMousePosition;

    bool dragging;
public:
    //get window at construct and initialize variables with initializer list
    ViewDragger(sf::RenderTarget& RTwindow)
        : RTwindow{ RTwindow }, dragging{}
    {
    }
    //use after window.pollEvent(event)) to get event handler
    void handleEvent(const sf::Event event, sf::View& view)
    {
        switch (event.type)
        {
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                //start dragging
                dragging = true;
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                //stop dragging
                dragging = false;
            }
            break;
        case sf::Event::MouseMoved:
            //get new mouse position
            const sf::Vector2i mousePosition(event.mouseMove.x, event.mouseMove.y);
            if (dragging)
            {
                //if mouse is dragging, count difference between new mouse position and old mouse position 
                //example: mouse move down by x100: new(x400,.y300) - (x300,y300) = x100 and for opposite direction make it -x100
                const sf::Vector2f delta = RTwindow.mapPixelToCoords(mousePosition) - RTwindow.mapPixelToCoords(previousMousePosition);
                view.move(-delta);
                //update view
                RTwindow.setView(view);

            }
            //save current mouse position as old mouse position for next run
            previousMousePosition = mousePosition;
            break;
        }

    }
};