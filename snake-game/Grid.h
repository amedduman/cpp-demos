#pragma once
#include <vector>
#include "Cell.h"

class Grid
{
public:
    static constexpr int width = 20;
    static constexpr int height = 20;
    static constexpr int coloumCount = 40;
    static constexpr int rowCount = 30;

    Grid()
    {
        for (int v = 0; v < 600/height; ++v)
        {
            for (int h = 0; h < 800/width; ++h)
            {
                auto t = Cell(width,height, h, v);
                tiles.push_back(t);
            }
        }
    }

    void Draw(sf::RenderWindow& window) const
    {
        for (auto cell : tiles)
        {
            window.draw(cell.GetShape());
        }
    }

private:
    std::vector<Cell> tiles;
};