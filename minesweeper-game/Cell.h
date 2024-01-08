#pragma once
#include <SFML/Graphics.hpp>
#include "Blackboard.h"
#include <iostream>

class Cell
{
public:
    enum State
    {
        Hidden,
        Revealed,
        Flaged,
    };

    Cell(const int in_horizontalRank, const int in_verticalRank, const sf::Font& font)
    {
        pos = sf::Vector2i(in_horizontalRank * width + 300, in_verticalRank * height + 150);
        state = Hidden;

        sprite.setTexture(Blackboard::tileSet);
        sprite.setTextureRect(hiddenRect);
        flagSprite.setTexture(Blackboard::tileSet);
        flagSprite.setTextureRect(flagRect);
        sprite.setPosition(pos.x, pos.y);
        sprite.setScale(2,2);
        flagSprite.setPosition(pos.x, pos.y);
        flagSprite.setScale(2,2);

        cellNum.x = in_horizontalRank;
        cellNum.y = in_verticalRank;

        cellNumText = sf::Text();
        cellNumText.setFont(font);
        cellNumText.setString(std::to_string(cellNum.x) + ", " + std::to_string(cellNum.y));
        cellNumText.setCharacterSize(12);
        cellNumText.setPosition(pos.x - 25, pos.y - 25);
        cellNumText.setFillColor(sf::Color::White);
    }

    void Draw(sf::RenderWindow& window) const
    {
        window.draw(sprite);
        if(state == Flaged)
            window.draw(flagSprite);
    }

    void Reveal()
    {
        state = Revealed;
        sprite.setTextureRect(revealedRect);
    }

    void Flag()
    {
        state = Flaged;
    }

    State GetState() const
    {
        return state;
    }

    sf::Vector2i GetTileNum() const
    {
        return cellNum;
    }

    bool IsTileIncludePoint(const int x, const int y) const
    {
        return x >= pos.x && x <= pos.x + sprite.getGlobalBounds().width &&
               y >= pos.y && y <= pos.y + sprite.getGlobalBounds().height;
    }

    bool operator==(const Cell& other) const
    {
        return GetTileNum().x == other.GetTileNum().x && GetTileNum().y == other.GetTileNum().y;
    }

    bool operator!=(const Cell& other) const
    {
        return GetTileNum().x == other.GetTileNum().x && GetTileNum().y == other.GetTileNum().y;
    }

private:
    static constexpr int width = 32;
    static constexpr int height = 32;
    sf::Vector2i cellNum;
    sf::Text cellNumText;
    State state;
    sf::Vector2i pos;
    sf::Sprite sprite;
    sf::Sprite flagSprite;
    sf::IntRect hiddenRect = sf::IntRect(32,48,16,16);
    sf::IntRect revealedRect = sf::IntRect(0,64,16,16);
    sf::IntRect flagRect = sf::IntRect(32,0,16,16);
    sf::IntRect mineRect;
};
