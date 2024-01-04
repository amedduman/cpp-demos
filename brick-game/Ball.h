#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>

class Ball
{
public:
    Ball()
    {
        shape.setPosition(sf::Vector2f(400,300));
        shape.setSize(sf::Vector2f(10,10));
        shape.setOrigin(sf::Vector2f(5,5));
        velocity = sf::Vector2f(-3,3);
    }
    void Move()
    {
        if(isStopped) return;
        auto pos = shape.getPosition();
        pos += velocity;
        shape.setPosition(pos);
    }
    void Pause()
    {
        isStopped = true;
    }
    void UnPause()
    {
        isStopped = false;
    }
    void ReboundIfExceedBoundary(const sf::Rect<float>& rect)
    {
        const auto pos = shape.getPosition();
        const auto size = shape.getSize();

        if(pos.x - size.x  < rect.left)
            velocity.x *= -1;
        if(pos.x + size.x > rect.left + rect.width)
            velocity.x *= -1;
        if(pos.y - size.y < rect.top)
            velocity.y *= -1;
        if(pos.y + size.y > rect.top +rect.height)
            velocity.y *= -1;
    }
    const sf::RectangleShape& GetShape() const
    {
        return shape;
    }
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    bool isStopped = false;
};
