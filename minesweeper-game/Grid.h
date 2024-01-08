#pragma once

#include <vector>

#include "Blackboard.h"
#include "Cell.h"

class Grid
{
public:
    static constexpr int coloumCount = 8;
    static constexpr int rowCount = 6;

    Grid() = default;

    explicit Grid(const sf::Font& gameFont)
    {
        background.setTexture(Blackboard::tileSet);
        background.setTextureRect(sf::IntRect(48,48,16,16));
        background.setScale(12,16);
        background.setPosition(300,150);

        for (int v = 0; v < coloumCount; ++v)
        {
            for (int h = 0; h < rowCount; ++h)
            {
                auto t = Cell(h, v, gameFont);
                cells.push_back(t);
            }
        }
    }

    void Draw(sf::RenderWindow& window) const
    {
        window.draw(background);
        for (auto cell : cells)
        {
            cell.Draw(window);
        }
    }

    void RevealCell(const int x, const int y)
    {
        for (auto& cell : cells)
        {
            if(cell.IsTileIncludePoint(x,y) && cell.GetState() == Cell::State::Hidden)
                cell.Reveal();
        }
    }

    void FlagCell(const int x, const int y)
    {
        for (auto& cell : cells)
        {
            if(cell.IsTileIncludePoint(x,y) && cell.GetState() == Cell::State::Hidden)
                cell.Flag();
        }
    }

private:
    std::vector<Cell> cells;
    sf::Sprite background;
};
