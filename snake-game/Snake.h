#pragma once
#include <vector>
#include "SnakeSegment.h"

class Snake
{
public:
    explicit Snake(const sf::Vector2i startingGridPos)
    {
        const auto segment = SnakeSegment(startingGridPos, true);
        const auto segment2 = SnakeSegment(startingGridPos);
        const auto segment3 = SnakeSegment(startingGridPos);
        segments.push_back(segment);
        segments.push_back(segment2);
        segments.push_back(segment3);
    }

    void Draw(sf::RenderWindow& window) const
    {
        for (auto& s : segments)
            s.Draw(window);
    }

    void Move(const sf::Vector2i deltaMove)
    {
        for (int i = segments.size() - 1; i >= 0; --i)
        {
            if(segments[i].IsHead())
                segments[i].Move(deltaMove);
            else if(i - 1 >= 0)
                segments[i].Follow(segments[i-1]);
        }
    }

    const SnakeSegment& GetHead() const
    {
        return segments[0];
    }

    void Grow()
    {
        const auto segment = SnakeSegment(segments[segments.size()-1].GetGridPos());
        segments.push_back(segment);
    }

    bool IsSnakeOccupiesThisTile(const sf::Vector2i cellIndex) const
    {
        for (auto& s : segments)
        {
            const auto segmentGridPos = s.GetGridPos();
            if (cellIndex == segmentGridPos)
            {
                return true;
            }
        }

        return false;
    }
private:
    std::vector<SnakeSegment> segments;
};