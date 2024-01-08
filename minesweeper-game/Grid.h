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

    void RevealAllCells()
    {
        for (auto& cell : cells)
        {
            cell.GameEndReveal();
        }
    }

    void RevealCell(const int x, const int y)
    {
        for (auto& cell : cells)
        {
            if(cell.IsTileIncludePoint(x,y) && cell.GetState() == Cell::State::Hidden)
            {
                auto num = cell.GetTileNum();

                int adjacentMineCount = 0;
                const sf::Vector2i left(num.x-1,num.y);
                const sf::Vector2i right(num.x+1,num.y);
                const sf::Vector2i up(num.x,num.y-1);
                const sf::Vector2i down(num.x,num.y+1);

                if(TryGetCell(left)  && TryGetCell(left) ->HasMine()) adjacentMineCount++;
                if(TryGetCell(right) && TryGetCell(right)->HasMine()) adjacentMineCount++;
                if(TryGetCell(up)    && TryGetCell(up)   ->HasMine()) adjacentMineCount++;
                if(TryGetCell(down)  && TryGetCell(down) ->HasMine()) adjacentMineCount++;
                // if(TryGetCell(num.x - 1,num.y - 1) && TryGetCell(num.x - 1, num.y)->HasMine()) adjacentMineCount++;
                // if(TryGetCell(num.x - 1,num.y + 1) && TryGetCell(num.x - 1, num.y)->HasMine()) adjacentMineCount++;
                // if(TryGetCell(num.x + 1,num.y + 1) && TryGetCell(num.x - 1, num.y)->HasMine()) adjacentMineCount++;
                // if(TryGetCell(num.x + 1,num.y - 1) && TryGetCell(num.x - 1, num.y)->HasMine()) adjacentMineCount++;
                cell.Reveal(adjacentMineCount);
            }
        }
    }

    const Cell* TryGetCell(const sf::Vector2i num) const
    {
        for (auto& cell : cells)
        {
            if(num.x == cell.GetTileNum().x && num.y == cell.GetTileNum().y )
            {
                return &cell;
            }
        }
        return nullptr;
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
