#pragma once
#include <SFML/Graphics.hpp>

class StarterDemo
{
public:
    sf::RenderWindow m_window;

    StarterDemo()
        :m_window(sf::VideoMode(800, 600), "My window")
    {}

    void Run()
    {
        while (m_window.isOpen())
        {
            Input();
            Render();
        }
    }
private:
    void Input()
    {
        sf::Event event {};
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    m_window.close();
                }
                if(event.key.code == sf::Keyboard::Escape)
                {
                    m_window.close();
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
        m_window.clear(sf::Color(25, 35,25));

        m_window.display();
    }
};