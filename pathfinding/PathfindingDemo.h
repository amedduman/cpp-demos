#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

struct Tile
{
    Tile(const int in_width, const int in_height, const int in_horizontalRank, const int in_verticalRank, const sf::Font& font)
    {
        pos = sf::Vector2i(in_horizontalRank * in_width, in_verticalRank * in_height);
        width = in_width;
        height = in_height;

        shape = sf::RectangleShape();
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineThickness(1);
        shape.setOutlineColor(sf::Color::White);
        shape.setSize(sf::Vector2f(in_width - 1, in_height - 1));
        shape.setPosition(pos.x, pos.y);

        tileNumberText = sf::Text();
        tileNumberText.setFont(font);
        tileNumberText.setString(std::to_string(in_horizontalRank) + ", " + std::to_string(in_verticalRank));
        tileNumberText.setCharacterSize(16);
        tileNumberText.setPosition(pos.x, pos.y);
        tileNumberText.setFillColor(sf::Color::White);
    }

    const sf::RectangleShape& GetShape()
    {
        return shape;
    }

    const sf::Text& GetText()
    {
        return tileNumberText;
    }

    bool IsTileIncludePoint(const sf::Vector2i& point) const
    {
        return point.x >= pos.x && point.x <= pos.x + width &&
               point.y >= pos.y && point.y <= pos.y + height;
    }

    void AddBlock()
    {
        isBlocked = true;
        shape.setFillColor(sf::Color(0,100,100));
    }

    void RemoveBlock()
    {
        isBlocked = false;
        shape.setFillColor(sf::Color::Transparent);
    }

    bool IsBlocked() const
    {
        return isBlocked;
    }

private:
    sf::RectangleShape shape;
    sf::Text tileNumberText;
    sf::Vector2i pos;
    int width;
    int height;
    bool isBlocked = false;
};

class PathfindingDemo
{
public:
    sf::RenderWindow window;
    std::vector<Tile> tiles;
    bool isShiftPressed = false;
    sf::Font font;

    PathfindingDemo()
        :window(sf::VideoMode(800, 600), "My window")
    {
        int width = 50;
        int height = 50;

        if (!font.loadFromFile("../play.ttf"))
        {
            std::cout << "can't load font" << std::endl;
        }

        for (int v = 0; v < 600/height; ++v)
        {
            for (int h = 0; h < 800/width; ++h)
            {
                auto t = Tile(width,height, h, v, font);
                tiles.push_back(t);
            }
        }
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
                if(event.key.code == sf::Keyboard::LShift)
                {
                    isShiftPressed = true;
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::LShift)
                {
                    isShiftPressed = false;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (isShiftPressed)
                    {
                        PutBlock();
                    }
                    else
                    {
                        DetectNeighbours();
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    RemoveBlock();
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {

            }
        }
    }
    void Render()
    {
        window.clear(sf::Color(25, 35,25));

        for (auto& t : tiles)
        {
            window.draw(t.GetShape());
            window.draw(t.GetText());
        }

        window.display();
    }

    void PutBlock()
    {
        const auto mousePos = sf::Mouse::getPosition(window);

        for(auto& t : tiles)
        {
            if(t.IsTileIncludePoint(mousePos))
            {
                if(t.IsBlocked()) break;
                t.AddBlock();
                break;
            }
        }
    }

    void RemoveBlock()
    {
        const auto mousePos = sf::Mouse::getPosition(window);

        for(auto& t : tiles)
        {
            if(t.IsTileIncludePoint(mousePos))
            {
                if(t.IsBlocked() == false) break;
                t.RemoveBlock();
                break;
            }
        }
    }

    void DetectNeighbours()
    {
        std::vector<Tile> neighbourTiles;
        int tileIndex = 0;

        const auto mousePos = sf::Mouse::getPosition(window);
        for (int i = 0; i < tiles.size(); ++i)
        {
            if(tiles[i].IsTileIncludePoint(mousePos))
            {
                if(tiles[i].IsBlocked()) return;
            }
        }



    }
};