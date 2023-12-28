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

        std::get<0>(tileNum) = in_horizontalRank;
        std::get<1>(tileNum) = in_verticalRank;

        tileNumberText = sf::Text();
        tileNumberText.setFont(font);
        tileNumberText.setString(std::to_string(std::get<0>(tileNum)) + ", " + std::to_string(std::get<1>(tileNum)));
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

    sf::Vector2i GetTileNum() const
    {
        const int w = std::get<0>(tileNum);
        const int h = std::get<1>(tileNum);
        return {w,h};
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
    std::tuple<int,int> tileNum;
};

class PathfindingDemo
{
public:
    sf::RenderWindow window;
    std::vector<Tile> tiles;
    bool isShiftPressed = false;
    sf::Font font;
    int width = 50;
    int height = 50;

    PathfindingDemo()
        :window(sf::VideoMode(800, 600), "My window")
    {
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
        std::vector<Tile*> neighbourTiles;

        neighbourTiles.push_back(&tiles[0]);
        neighbourTiles.push_back(&tiles[1]);

        const auto mousePos = sf::Mouse::getPosition(window);
        for (const auto & tile : tiles)
        {
            if(tile.IsTileIncludePoint(mousePos))
            {
                if(tile.IsBlocked()) return;

                const auto w = tile.GetTileNum().x;
                const auto h = tile.GetTileNum().y;

                const auto r = GetTileAt(w + 1, h    );
                const auto l = GetTileAt(w - 1, h    );
                const auto u = GetTileAt(w    , h + 1);
                const auto d = GetTileAt(w    , h - 1);

                if(r != nullptr) r->AddBlock();
                if(l != nullptr) l->AddBlock();
                if(u != nullptr) u->AddBlock();
                if(d != nullptr) d->AddBlock();
            }
        }
    }

    Tile* GetTileAt(const int w, const int h)
    {
        for(auto& t : tiles)
        {
            if(t.GetTileNum().x == w && t.GetTileNum().y == h)
                return &t;
        }

        return nullptr;
    }
};