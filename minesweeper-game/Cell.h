#pragma once
#include <SFML/Graphics.hpp>

class Cell
{
public:
    Cell(const int in_width, const int in_height, const int in_horizontalRank, const int in_verticalRank, const sf::Font& font)
    {
        pos = sf::Vector2i(in_horizontalRank * in_width, in_verticalRank * in_height);
        width = in_width;
        height = in_height;

        shape = sf::RectangleShape();
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineThickness(1);
        shape.setOutlineColor(sf::Color::White);
        shape.setSize(sf::Vector2f(in_width - 1, in_height - 1));
        shape.setPosition(pos.x, pos.y);

        cellNum.x = in_horizontalRank;
        cellNum.y = in_verticalRank;

        cellNumText = sf::Text();
        cellNumText.setFont(font);
        cellNumText.setString(std::to_string(cellNum.x) + ", " + std::to_string(cellNum.y));
        cellNumText.setCharacterSize(12);
        cellNumText.setPosition(pos.x, pos.y);
        cellNumText.setFillColor(sf::Color::White);

        value = 0;

        valueText = sf::Text();
        valueText.setFont(font);
        valueText.setString(std::to_string(value));
        valueText.setCharacterSize(12);
        valueText.setOrigin(6,6);
        valueText.setPosition(pos.x + width / 2 , pos.y + height / 2);
        valueText.setFillColor(sf::Color::Yellow);
    }

    const sf::RectangleShape& GetShape()
    {
        return shape;
    }

    const sf::Text& GetTileNumText()
    {
        return cellNumText;
    }

    const sf::Text& GetTileValueText()
    {
        return valueText;
    }

    sf::Vector2i GetTileNum() const
    {
        return cellNum;
    }

    bool IsTileIncludePoint(const sf::Vector2i& point) const
    {
        return point.x >= pos.x && point.x <= pos.x + width &&
               point.y >= pos.y && point.y <= pos.y + height;
    }

    void ColorTile(const sf::Color& color)
    {
        shape.setFillColor(color);
    }

    void ResetTileColor()
    {
        shape.setFillColor(sf::Color::Transparent);
    }

    bool IsBlocked() const
    {
        return value == -1;
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
    sf::RectangleShape shape;
    sf::Text cellNumText;
    sf::Text valueText;
    sf::Vector2i pos;
    int width;
    int height;
    sf::Vector2i cellNum;
    int value;
};
