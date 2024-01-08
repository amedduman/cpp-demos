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

        if(rand() % 10 < 5) hasMine = true;

        flagSprite.setTexture(Blackboard::tileSet);
        flagSprite.setTextureRect(flagRect);
        flagSprite.setPosition(pos.x, pos.y);
        flagSprite.setScale(2,2);

        sprite.setTexture(Blackboard::tileSet);
        sprite.setTextureRect(hiddenRect);
        sprite.setPosition(pos.x, pos.y);
        sprite.setScale(2,2);

        cellNum.x = in_horizontalRank;
        cellNum.y = in_verticalRank;

        adjacentMineCountText = sf::Text();
        adjacentMineCountText.setFont(font);
        adjacentMineCountText.setCharacterSize(9);
        adjacentMineCountText.setPosition(pos.x + 16, pos.y + 8);
        adjacentMineCountText.setFillColor(sf::Color::White);
    }

    void Draw(sf::RenderWindow& window) const
    {
        window.draw(adjacentMineCountText);
        window.draw(sprite);
        if(state == Flaged)
            window.draw(flagSprite);
    }

    void GameEndReveal()
    {
        if(hasMine )
        {
            if(isExploded == false)
                sprite.setTextureRect(mineRect);
                else
                    sprite.setTextureRect(mineExplodeRect);
        }
        else
            sprite.setTextureRect(revealedRect);
    }

    void Reveal(const int adjacentMineCount)
    {
        if(adjacentMineCount != 0)
            adjacentMineCountText.setString(std::to_string(adjacentMineCount));
        state = Revealed;
        if(hasMine)
        {
            isExploded = true;
            sprite.setTextureRect(mineExplodeRect);
            Blackboard::IsGameOver = true;
        }
        else
            sprite.setTextureRect(revealedRect);
    }

    void Color()
    {
        sprite.setColor(sf::Color::Yellow);
    }

    void Flag()
    {
        state = Flaged;
    }

    State GetState() const
    {
        return state;
    }

    bool HasMine() const
    {
        return hasMine;
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
    State state;
    bool hasMine = false;
    bool isExploded = false;
    sf::Text adjacentMineCountText;
    sf::Vector2i pos;
    sf::Sprite sprite;
    sf::Sprite flagSprite;
    sf::IntRect hiddenRect = sf::IntRect(32,48,16,16);
    sf::IntRect revealedRect = sf::IntRect(0,64,16,16);
    sf::IntRect flagRect = sf::IntRect(32,0,16,16);
    sf::IntRect mineRect = sf::IntRect(0,0,16,16);
    sf::IntRect mineExplodeRect = sf::IntRect(48,0,16,16);
};
