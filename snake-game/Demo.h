#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Food.h"
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
    bool canInput;
    Food food;
    bool canRun = true;

    Demo()
        :window(sf::VideoMode(800, 600), "demo"),
        snake(sf::Vector2i(4,4))
    {
        window.setFramerateLimit(60);
        snakeMoveVec = sf::Vector2i(1,0);
        canInput = true;

        auto foodPos = grid.GetAvailableCell(snake);
        food.SetGridPosition(foodPos);
    }

    void Run()
    {
        while (window.isOpen())
        {
            currentFrame++;
            Input();
            Render();

            if(currentFrame %20 == 0 &&  canRun)
            {
                snake.Move(snakeMoveVec);
                canInput = true;

                if(snake.CheckSelfCollide())
                    canRun = false;

                if(food.HasEaten(snake))
                {
                    snake.Grow();
                    food.SetGridPosition(grid.GetAvailableCell(snake));
                }
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
                if(canInput)
                {
                    if(event.key.code == sf::Keyboard::W)
                    {
                        if(snakeMoveVec.y == 1) return;
                        snakeMoveVec = sf::Vector2i(0, -1);
                        canInput = false;
                    }
                    if(event.key.code == sf::Keyboard::S)
                    {
                        if(snakeMoveVec.y == -1) return;
                        snakeMoveVec = sf::Vector2i(0, 1);
                        canInput = false;
                    }
                    if(event.key.code == sf::Keyboard::A)
                    {
                        if(snakeMoveVec.x == 1) return;
                        snakeMoveVec = sf::Vector2i(-1, 0);
                        canInput = false;
                    }
                    if(event.key.code == sf::Keyboard::D)
                    {
                        if(snakeMoveVec.x == -1) return;
                        snakeMoveVec = sf::Vector2i(1, 0);
                        canInput = false;
                    }
                }

                if(event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                if(event.key.code == sf::Keyboard::Space)
                {
                    snake.Grow();
                }
            }
        }
    }

    void Render()
    {
        window.clear(sf::Color(130, 150,150));

        // grid.Draw(window);
        snake.Draw(window);
        food.Draw(window);

        window.display();
    }
};