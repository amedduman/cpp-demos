#pragma once
#include "Snake.h"

class Food
{
public:
    Food()
    {
        shape.setPosition( 0,0);
        shape.setSize(sf::Vector2f(16, 16));
        shape.setOrigin(-2,-2);
        shape.setFillColor(sf::Color::Yellow);
    }

    void SetGridPosition(sf::Vector2i gridPos)
    {
        myGridPos = gridPos;
        shape.setPosition( gridPos.x * 20, gridPos.y * 20);
    }

    bool HasEaten(const Snake& snake)
    {
        return myGridPos == snake.GetHead().GetGridPos();
    }

    void Draw(sf::RenderWindow& window)
    {
        window.draw(shape);
    }
private:
    sf::RectangleShape shape;
    sf::Vector2i myGridPos;
};
