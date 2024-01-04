#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

class Paddle
{
public:
    Paddle()
    {
        shape.setSize(sf::Vector2f(100,200));
        shape.setPosition(350, 550);
        shape.setOrigin(50, 100);
        shape.setFillColor(sf::Color::Cyan);
    }
    void Move(const int deltaMoveX)
    {
        auto pos = shape.getPosition();
        pos.x += static_cast<float>(deltaMoveX) * speed;
        shape.setPosition(pos);
    }
    const sf::RectangleShape& GetShape() const
    {
        return shape;
    }
private:
    sf::RectangleShape shape;
    float speed = 5;
};
