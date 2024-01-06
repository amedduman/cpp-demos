#pragma once
#include <SFML/Graphics.hpp>
#include "Blackboard.h"
#include "Grid.h"
#include <iostream>

class Demo
{
public:
    sf::RenderWindow window;
    sf::Font font;
    Grid grid;


    Demo()
        :window(sf::VideoMode(Blackboard::windowW, Blackboard::windowH), "Demo")
    {
        if (!font.loadFromFile("../Rubik.ttf"))
        {
            std::cout << "can't load font" << std::endl;
        }

        grid = Grid(font);
    }

    void Run()
    {
        while (window.isOpen())
        {
            Input();
            Render();
        }
    }
private:
    void Input()
    {
        sf::Event event {};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                if(event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                if(event.key.code == sf::Keyboard::Space)
                {
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {

            }
        }
    }
    void Render()
    {
        window.clear(sf::Color(25, 35,25));

        grid.Draw(window);

        window.display();
    }
};
