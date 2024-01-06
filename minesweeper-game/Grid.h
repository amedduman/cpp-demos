#pragma once

#include <vector>

#include "Blackboard.h"
#include "Cell.h"

class Grid
{
public:
    static constexpr int width = 80;
    static constexpr int height = 60;
    static constexpr int coloumCount = 40;
    static constexpr int rowCount = 30;

    Grid() = default;

    explicit Grid(const sf::Font& gameFont)
    {
        for (int v = 0; v < Blackboard::windowH/height; ++v)
        {
            for (int h = 0; h < Blackboard::windowW/width; ++h)
            {
                auto t = Cell(width,height, h, v, gameFont);
                cells.push_back(t);
            }
        }
    }

    void Draw(sf::RenderWindow& window) const
    {
        for (auto cell : cells)
        {
            window.draw(cell.GetShape());
            window.draw(cell.GetTileNumText());
        }
    }

private:
    std::vector<Cell> cells;
};
