#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <set>

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

        value = 0;

        valueText = sf::Text();
        valueText.setFont(font);
        valueText.setString(std::to_string(value));
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

    void ResetTileColor()
    {
        shape.setFillColor(sf::Color::Transparent);
    }

    void AddBlock()
    {
        value = -1;
        valueText.setString(std::to_string(value));
        shape.setFillColor(sf::Color(0,100,100));
    }

    void RemoveBlock()
    {
        value = 0;
        valueText.setString(std::to_string(value));
        shape.setFillColor(sf::Color::Transparent);
    }

    bool IsBlocked() const
    {
        return value == -1;
    }

    void SetValue(const int in_value)
    {
        value = in_value;
        valueText.setString(std::to_string(value));
    }

    int GetValue() const
    {
        return value;
    }

    bool operator==(const Tile& other) const
    {
        return GetTileNum().x == other.GetTileNum().x && GetTileNum().y == other.GetTileNum().y;
    }

    bool operator!=(const Tile& other) const
    {
        return GetTileNum().x == other.GetTileNum().x && GetTileNum().y == other.GetTileNum().y;
    }

private:
    sf::RectangleShape shape;
    sf::Text tileNumberText;
    sf::Text valueText;
    sf::Vector2i pos;
    int width;
    int height;
    std::tuple<int,int> tileNum;
    int value;
};

class Mover
{
public:
    Mover() = default;
    explicit Mover(Tile* in_tile)
    {
        myTile = in_tile;
        shape.setRadius(25);
        shape.setPosition(in_tile->GetShape().getPosition());
        currentIndexInPath = -1;
    }
    void ResetPath()
    {
        currentIndexInPath = -1;
    }
    void Move(std::vector<Tile*>& path)
    {
        if(path.size() <= 0) return;
        currentIndexInPath++;
        if(currentIndexInPath >= path.size()) return;
        const auto tile = path[currentIndexInPath];
        myTile = tile;
        shape.setPosition(tile->GetShape().getPosition());
    }
    Tile* GetTile() const
    {
        return myTile;
    }
    const sf::CircleShape& GetShape()
    {
        return shape;
    }
private:
    Tile* myTile;
    sf::CircleShape shape;
    int currentIndexInPath;
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
    std::vector<Tile*> path;
    Mover mover;
    int curentFrame = 0;


    PathfindingDemo()
        :window(sf::VideoMode(800, 600), "My window")
    {
        window.setFramerateLimit(60);

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

        mover = Mover(&tiles[40]);
    }

    void Run()
    {
        while (window.isOpen())
        {
            Input();
            Render();

            if(curentFrame %10 == 0)
            {
                mover.Move(path);
                int index = path.size() - 1;
                if (index >= 0)
                {
                    if(path[path.size()-1] == mover.GetTile())
                    {
                        ResetTileColors();
                        path.clear();
                    }
                }
            }

            curentFrame++;
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
                    CalculateTileValues(&tiles[0], &tiles[30]);
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
                        CalculateTileValues(mover.GetTile(), GetTileUnderCursor());
                        TryFindPath(mover.GetTile(), GetTileUnderCursor());
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

        window.draw(mover.GetShape());

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

    Tile* GetTileUnderCursor()
    {
        const auto mousePos = sf::Mouse::getPosition(window);
        for (auto & tile : tiles)
        {
            if(tile.IsTileIncludePoint(mousePos))
            {
                return &tile;
            }
        }

        return nullptr;
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

    std::vector<Tile*> DetectNeighbours(const Tile& tile)
    {
        std::vector<Tile*> tiles;
        if(tile.IsBlocked()) return tiles;

        const auto w = tile.GetTileNum().x;
        const auto h = tile.GetTileNum().y;

        const auto r = GetTileAt(w + 1, h    );
        const auto l = GetTileAt(w - 1, h    );
        const auto u = GetTileAt(w    , h + 1);
        const auto d = GetTileAt(w    , h - 1);

        if(r != nullptr) tiles.push_back(r);
        if(l != nullptr) tiles.push_back(l);
        if(u != nullptr) tiles.push_back(u);
        if(d != nullptr) tiles.push_back(d);

        return tiles;
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

    void CalculateTileValues(Tile* startTile, Tile* endTile)
    {
        for (auto& t : tiles)
        {
            if(t.IsBlocked()) continue;
            t.SetValue(0);
        }

        int value = 1;

        std::set<Tile*> processingTiles;
        std::set<Tile*> newlyDiscoveredTiles;

        processingTiles.insert(endTile);

        while (true)
        {
            for (auto t : processingTiles)
            {
                t->SetValue(value);

                for (auto nt : DetectNeighbours(*t))
                {
                    if(nt->GetValue() == 0)
                    {
                        newlyDiscoveredTiles.insert(nt);
                    }
                }
            }

            if(newlyDiscoveredTiles.empty())
                break;

            processingTiles.clear();
            processingTiles = newlyDiscoveredTiles;
            newlyDiscoveredTiles.clear();
            value++;
        }
    }

    bool TryFindPath(Tile* startTile, Tile* endTile)
    {
        ResetTileColors();

        startTile->ColorTile(sf::Color::Green);
        endTile->ColorTile(sf::Color::Red);

        mover.ResetPath();
        path.clear();

        const Tile* currentTile = startTile;

        while (true)
        {
            int lowestValue = 9999;
            Tile* nearestTile = nullptr;
            for (const auto nt : DetectNeighbours(*currentTile))
            {
                if(nt->GetValue() < lowestValue && nt->IsBlocked() == false)
                {
                    lowestValue = nt->GetValue();
                    nearestTile = nt;
                }
            }

            if(nearestTile == nullptr)
            {
                path.clear();
                return false;
            }

            path.push_back(nearestTile);

            if (nearestTile == endTile)
            {
                return true;
            }

            nearestTile->ColorTile(sf::Color(100,100,100));

            currentTile = nearestTile;
        }
    }

    void ResetTileColors()
    {
        for(auto& t : tiles)
        {
            if(t.IsBlocked() == false)
                t.ResetTileColor();
        }
    }
};