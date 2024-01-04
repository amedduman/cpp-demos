#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

class Paddle
{
public:
    Paddle()
    {
        shape.setSize(sf::Vector2f(100,20));
        shape.setPosition(350, 550);
        shape.setFillColor(sf::Color::Cyan);
    }
    const sf::RectangleShape& GetShape() const
    {
        return shape;
    }
private:
    sf::RectangleShape shape;
};
