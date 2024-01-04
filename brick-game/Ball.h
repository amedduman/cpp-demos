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
        shape.setOrigin(sf::Vector2f(10,10));
        velocity = sf::Vector2f(-1l,1);
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
        const auto radius = shape.getRadius();

        if(pos.x - radius  < rect.left)
            velocity.x *= -1;
        if(pos.x + radius > rect.left + rect.width)
            velocity.x *= -1;
        if(pos.y - radius < rect.top)
            velocity.y *= -1;
        if(pos.y + radius > rect.top +rect.height)
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
