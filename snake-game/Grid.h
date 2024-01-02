#pragma once
#include <vector>
#include "Cell.h"
#include "Snake.h"

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
                cells.push_back(t);
            }
        }
    }

    void Draw(sf::RenderWindow& window) const
    {
        for (auto cell : cells)
        {
            window.draw(cell.GetShape());
        }
    }

    sf::Vector2i GetAvailableCell(const Snake& snake)
    {
        int w = 0;
        int h = 0;
        do
        {
            w = rand() & width;
            h = rand() & height;
        }while (snake.IsSnakeOccupiesThisTile(sf::Vector2i(w, h)));

        return sf::Vector2i(w,h);
    }


private:
    std::vector<Cell> cells;
};
