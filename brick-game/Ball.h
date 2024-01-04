#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>

class Ball
{
public:
    Ball()
    {
        shape.setPosition(sf::Vector2f(400,300));
        shape.setRadius(10);

        velocity = sf::Vector2f(-5,1);
    }
    void Move()
    {
        auto pos = shape.getPosition();
        pos += velocity;
        shape.setPosition(pos);
    }
    void ReboundIfExceedBoundary(const sf::Rect<float>& rect)
    {
        const auto pos = shape.getPosition();
        if(pos.x < rect.left)
            velocity.x *= -1;
        if(pos.x > rect.left + rect.width)
            velocity.x *= -1;
        if(pos.y < rect.top)
            velocity.y *= -1;
        if(pos.y > rect.top +rect.height)
            velocity.y *= -1;
    }
    const sf::CircleShape& GetShape() const
    {
        return shape;
    }
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
};
