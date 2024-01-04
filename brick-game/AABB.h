#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

class AABB
{
public:
    // rects origins should be centered
    static sf::Vector2f GetOverlapArea(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2)
    {
        const auto pos1 = rect1.getPosition();
        const auto pos2 = rect2.getPosition();
        const auto halfWidth1 = rect1.getSize().x/2;
        const auto halfHeight1 = rect1.getSize().y/2;
        const auto halfWidth2 = rect2.getSize().x/2;
        const auto halfHeight2 = rect2.getSize().y/2;
        const float dx = abs(pos1.x - pos2.x);
        const float dy = abs(pos1.y - pos2.y);
        const auto overlapArea = sf::Vector2f(halfWidth1 + halfWidth2 - dx, halfHeight1 + halfHeight2 - dy);
        return overlapArea;
    }
};
