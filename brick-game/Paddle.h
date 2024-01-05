#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

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

        canMove = true;
    }
    void Move(const int deltaMoveX)
    {
        if(!canMove) return;
        auto pos = shape.getPosition();
        previousPos = pos;
        pos.x += static_cast<float>(deltaMoveX) * speed;
        shape.setPosition(pos);
    }
    void SetPos(sf::Vector2f pos)
    {
        shape.setPosition(pos);
    }
    void Pause()
    {
        canMove = false;
    }
    void UnPause()
    {
        canMove = true;
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
    bool canMove;
};
