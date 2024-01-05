#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>

#include "Blackboard.h"

class Ball
{
public:
    Ball()
    {
        const auto pos = sf::Vector2f(300,300);
        const auto size = sf::Vector2f(10,10);

        previousPos = pos;

        shape.setPosition(pos);
        shape.setSize(size);
        shape.setOrigin(size.x/2, size.y/2);

        velocity = sf::Vector2f(3,-3);
    }
    void Move()
    {
        auto pos = shape.getPosition();
        previousPos = pos;
        pos += velocity;
        shape.setPosition(pos);

        if(pos.y > Blacboard::wH)
            Blacboard::isGameOver = true;
    }
    sf::Vector2f GetPreviousPos() const
    {
        return previousPos;
    }
    void SetPos(sf::Vector2f pos)
    {
        shape.setPosition(pos);
    }
    void ReboundX()
    {
        velocity.x *= -1;
    }
    void ReboundY()
    {
        velocity.y *= -1;
    }
    sf::Vector2f GetVelocity() const
    {
        return velocity;
    }
    void AddVel(const float velx, const float vely)
    {
        velocity += sf::Vector2f(velx, vely);
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
        // if(pos.y + size.y > rect.top +rect.height)
        //     velocity.y *= -1;
    }
    const sf::RectangleShape& GetShape() const
    {
        return shape;
    }
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f previousPos;
};
