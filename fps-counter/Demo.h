#pragma once
#include <SFML/Graphics.hpp>
#include "FrameTimer.h"

class Demo
{
public:
    sf::RenderWindow window;
    FrameTimer ft;
    int frameCount = 0;

    Demo()
        :window(sf::VideoMode(800, 600), "Demo")
    {
        window.setFramerateLimit(60);
    }

    void Run()
    {
        while (window.isOpen())
        {
            const float dt = ft.DeltaTime();
            frameCount++;
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

        window.display();
    }
};