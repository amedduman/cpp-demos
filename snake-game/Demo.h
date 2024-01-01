#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Snake.h"

class Demo
{
public:
    sf::RenderWindow window;
    int currentFrame = 0;
    Grid grid;
    Snake snake;

    Demo()
        :window(sf::VideoMode(800, 600), "demo"),
        grid(),
        snake(sf::Vector2i(4,4))
    {
        window.setFramerateLimit(60);
    }

    void Run()
    {
        while (window.isOpen())
        {
            currentFrame++;
            Input();
            Render();

            if(currentFrame %20 == 0)
            {
                printf("move");
                snake.Move(sf::Vector2i(1,0));
            }
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
            }
            if (event.type == sf::Event::KeyReleased)
            {
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
            }
        }
    }

    void Render()
    {
        window.clear(sf::Color(30, 30,30));

        grid.Draw(window);
        snake.Draw(window);

        window.display();
    }
};