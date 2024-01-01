#pragma once

class Cell
{
public:
    Cell(const int in_width, const int in_height, const int in_horizontalRank, const int in_verticalRank)
    {
        pos = sf::Vector2i(in_horizontalRank * in_width, in_verticalRank * in_height);
        width = in_width;
        height = in_height;

        shape = sf::RectangleShape();
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineThickness(1);
        shape.setOutlineColor(sf::Color::White);
        shape.setSize(sf::Vector2f(in_width, in_height));
        shape.setPosition(pos.x, pos.y);

        tileNum.x = in_horizontalRank;
        tileNum.y = in_verticalRank;
    }

    const sf::RectangleShape& GetShape()
    {
        return shape;
    }

    sf::Vector2i GetTileNum() const
    {
        return tileNum;
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
    sf::Vector2i pos;
    int width;
    int height;
    sf::Vector2i tileNum;
};