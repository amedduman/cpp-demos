#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class SnakeSegment
{
public:
    explicit SnakeSegment(const sf::Vector2i gridPos, bool in_isHead = false)
    {
        myGridPos = gridPos;
        isHead = in_isHead;

        shape.setPosition( gridPos.x * 20, gridPos.y * 20);
        shape.setSize(sf::Vector2f(16, 16));
        shape.setOrigin(-2,-2);
    }
    void Draw(sf::RenderWindow& window) const
    {
        window.draw(shape);
    }
    void Move(const sf::Vector2i deltaMove)
    {
        myGridPos += deltaMove;
        if(myGridPos.x < 0)
            myGridPos.x = 39;
        if(myGridPos.y < 0)
            myGridPos.y = 29;
        myGridPos.x %= 40;
        myGridPos.y %= 30;

        shape.setPosition(myGridPos.x * 20, myGridPos.y * 20);
    }

    void Follow(const SnakeSegment& seg)
    {
        myGridPos = seg.GetGridPos();
        Move(sf::Vector2i(0,0));
    }

    void Color(sf::Color color)
    {
        shape.setFillColor(color);
    }

    bool IsHead() const
    {
        return isHead;
    }
    sf::Vector2i GetGridPos() const
    {
        return myGridPos;
    }
private:
    sf::RectangleShape shape;
    sf::Vector2i myGridPos;
    bool isHead;
};
