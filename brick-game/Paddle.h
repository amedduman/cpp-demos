#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

#include "Blackboard.h"

class Paddle
{
public:
    Paddle()
    {
        const auto pos = sf::Vector2f(350, 550);
        auto size = sf::Vector2f(100,20);

        previousPos = pos;

        shape.setPosition(pos);
        shape.setSize(sf::Vector2f(size));
        shape.setOrigin(size.x/2, size.y/2);
        shape.setFillColor(sf::Color::Cyan);
    }
    void Move(const int deltaMoveX)
    {
        auto pos = shape.getPosition();
        previousPos = pos;
        auto newX = pos.x + static_cast<float>(deltaMoveX) * speed;
        if(newX + shape.getSize().x/2 > Blacboard::wW - 1 || newX - shape.getSize().x/2 < 1) return;
        pos.x += static_cast<float>(deltaMoveX) * speed;
        shape.setPosition(pos);
    }
    void SetPos(sf::Vector2f pos)
    {
        shape.setPosition(pos);
    }
    sf::Vector2f GetPreviousPos() const
    {
        return previousPos;
    }
    const sf::RectangleShape& GetShape() const
    {
        return shape;
    }
private:
    sf::RectangleShape shape;
    float speed = 5;
    sf::Vector2f previousPos;
};
