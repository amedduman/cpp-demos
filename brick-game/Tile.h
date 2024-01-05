#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

class Tile
{
public:
    Tile()
    {
        const auto pos = sf::Vector2f(0, 0);
        auto size = sf::Vector2f(51,25);

        shape.setPosition(pos);
        shape.setSize(sf::Vector2f(size));
        shape.setOrigin(size.x/2, size.y/2);
        shape.setFillColor(sf::Color(rand()%255,rand()%255,rand()%255));
    }
    void SetPos(const float x, const float y)
    {
        shape.setPosition(x,y);
    }
    const sf::RectangleShape& GetShape() const
    {
        return shape;
    }
private:
    sf::RectangleShape shape;
};
