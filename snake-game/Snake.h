#pragma once
#include <vector>
#include "SnakeSegment.h"

class Snake
{
public:
    explicit Snake(const sf::Vector2i startingGridPos)
    {
        auto segment = SnakeSegment(startingGridPos, true);
        segment.Color(sf::Color::Green);
        segments.push_back(segment);
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

        for (int i = 0; i < segments.size(); ++i)
        {
            const float green = std::lerp(255, 100, static_cast<float>(i)/static_cast<float>(segments.size()));
            segments[i].Color(sf::Color(0,green,100));
        }
    }

    bool CheckSelfCollide()
    {
        auto headPos = GetHead().GetGridPos();

        for (int i = 1; i < segments.size(); ++i)
        {
            if(headPos == segments[i].GetGridPos()) return true;
        }
        return false;
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