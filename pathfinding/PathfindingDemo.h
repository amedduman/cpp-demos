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
        tileNumberText.setCharacterSize(12);
        tileNumberText.setPosition(pos.x, pos.y);
        tileNumberText.setFillColor(sf::Color::White);

        valueText = sf::Text();
        valueText.setFont(font);
        valueText.setString(std::to_string(4));
        valueText.setCharacterSize(12);
        valueText.setOrigin(6,6);
        valueText.setPosition(pos.x + width / 2 , pos.y + height / 2);
        valueText.setFillColor(sf::Color::Yellow);
    }

    const sf::RectangleShape& GetShape()
    {
        return shape;
    }

    const sf::Text& GetTileNumText()
    {
        return tileNumberText;
    }

    const sf::Text& GetTileValueText()
    {
        return valueText;
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

    void ColorTile(const sf::Color& color)
    {
        shape.setFillColor(color);
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
    sf::Text valueText;
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
                if(event.key.code == sf::Keyboard::Space)
                {
                    FindPath();
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
        window.clear(sf::Color(30, 30,30));

        for (auto& t : tiles)
        {
            window.draw(t.GetShape());
            window.draw(t.GetTileNumText());
            window.draw(t.GetTileValueText());
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

                if(r != nullptr) r->ColorTile(sf::Color::Blue);
                if(l != nullptr) l->ColorTile(sf::Color::Blue);
                if(u != nullptr) u->ColorTile(sf::Color::Blue);
                if(d != nullptr) d->ColorTile(sf::Color::Blue);
            }
        }
    }

    void DetectNeighbours(const Tile& tile)
    {
        if(tile.IsBlocked()) return;

        const auto w = tile.GetTileNum().x;
        const auto h = tile.GetTileNum().y;

        const auto r = GetTileAt(w + 1, h    );
        const auto l = GetTileAt(w - 1, h    );
        const auto u = GetTileAt(w    , h + 1);
        const auto d = GetTileAt(w    , h - 1);

        if(r != nullptr) r->ColorTile(sf::Color::Blue);
        if(l != nullptr) l->ColorTile(sf::Color::Blue);
        if(u != nullptr) u->ColorTile(sf::Color::Blue);
        if(d != nullptr) d->ColorTile(sf::Color::Blue);
    }

    Tile* GetTileAt(const int w, const int h)
    {
        for(auto& t : tiles)
        {
            if(t.IsBlocked() == false && t.GetTileNum().x == w && t.GetTileNum().y == h)
                return &t;
        }

        return nullptr;
    }

    void FindPath()
    {
        Tile& startingTile = tiles[0];
        int value = 1;
        bool hasReached = false;
        while (hasReached == false)
        {
            DetectNeighbours(startingTile);
            value++;
            if (value == 4)
                hasReached = true;
        }
    }
};