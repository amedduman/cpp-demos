#pragma once
#include <SFML/Graphics/Font.hpp>

class Blackboard
{
public:
    static sf::Font gameFont;
    inline static sf::Texture tileSet = sf::Texture();
    static constexpr int windowW = 800;
    static constexpr int windowH = 600;
};
