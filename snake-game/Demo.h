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
    sf::Vector2i snakeMoveVec;

    Demo()
        :window(sf::VideoMode(800, 600), "demo"),
        snake(sf::Vector2i(4,4))
    {
        window.setFramerateLimit(60);
        snakeMoveVec = sf::Vector2i(1,0);
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
                snake.Move(snakeMoveVec);
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
                if(event.key.code == sf::Keyboard::W)
                {
                    if(snakeMoveVec.y == 1) return;
                    snakeMoveVec = sf::Vector2i(0, -1);
                }
                if(event.key.code == sf::Keyboard::S)
                {
                    if(snakeMoveVec.y == -1) return;
                    snakeMoveVec = sf::Vector2i(0, 1);
                }
                if(event.key.code == sf::Keyboard::A)
                {
                    if(snakeMoveVec.x == 1) return;
                    snakeMoveVec = sf::Vector2i(-1, 0);
                }
                if(event.key.code == sf::Keyboard::D)
                {
                    if(snakeMoveVec.x == -1) return;
                    snakeMoveVec = sf::Vector2i(1, 0);
                }
                if(event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
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