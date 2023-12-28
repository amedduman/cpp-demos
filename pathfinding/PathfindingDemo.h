#pragma once
#include <SFML/Graphics.hpp>

struct Tile
{
public:
    sf::RectangleShape shape;

    Tile(int in_width, int in_height, int in_horizontalRank, int in_verticalRank)
    {
        shape = sf::RectangleShape();
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineThickness(1);
        shape.setOutlineColor(sf::Color::White);
        shape.setSize(sf::Vector2f(in_width, in_height));
        shape.setPosition(in_horizontalRank * in_width, in_verticalRank * in_height);
    }
private:
    sf::Vector2<int> pos;
};

class PathfindingDemo
{
public:
    sf::RenderWindow m_window;
    std::vector<Tile> tiles;

    PathfindingDemo()
        :m_window(sf::VideoMode(800, 600), "My window")
    {
        int width = 50;
        int height = 50;

        for (int v = 0; v < 600/height; ++v)
        {
            for (int h = 0; h < 800/width; ++h)
            {
                auto t = Tile(width,height, h, v);
                tiles.push_back(t);
            }
        }
    }

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

        for (auto& t : tiles)
        {
            m_window.draw(t.shape);
        }

        m_window.display();
    }
};