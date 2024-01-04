#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>

class Ball
{
public:
    Ball()
    {
        const auto pos = sf::Vector2f(300,100);
        const auto size = sf::Vector2f(20,10);

        previousPos = pos;

        shape.setPosition(pos);
        shape.setSize(size);
        shape.setOrigin(size.x/2, size.y/2);

        velocity = sf::Vector2f(0,3);
    }
    void Move()
    {
        if(isStopped) return;

        auto pos = shape.getPosition();
        previousPos = pos;
        pos += velocity;
        shape.setPosition(pos);
    }
    sf::Vector2f GetPreviousPos() const
    {
        return previousPos;
    }
    void SetPos(sf::Vector2f pos)
    {
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
    void ReboundX()
    {
        velocity.x *= -1;
    }
    void ReboundY()
    {
        velocity.y *= -1;
    }
    void AddVel(const float velx, const float vely)
    {
        velocity += sf::Vector2f(velx, vely);

        std::cout << velocity.x << ", " << velocity.y << std::endl;
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
    sf::Vector2f previousPos;
};
