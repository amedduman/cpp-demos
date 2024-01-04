#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

class AABB
{
public:
    // rects origins should be centered
    // static sf::Vector2f GetOverlapArea(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2)
    // {
    //     const auto pos1 = rect1.getPosition();
    //     const auto pos2 = rect2.getPosition();
    //     const auto halfWidth1 = rect1.getSize().x/2;
    //     const auto halfHeight1 = rect1.getSize().y/2;
    //     const auto halfWidth2 = rect2.getSize().x/2;
    //     const auto halfHeight2 = rect2.getSize().y/2;
    //     const float dx = abs(pos1.x - pos2.x);
    //     const float dy = abs(pos1.y - pos2.y);
    //     const auto overlapArea = sf::Vector2f(halfWidth1 + halfWidth2 - dx, halfHeight1 + halfHeight2 - dy);
    //     return overlapArea;
    // }

    // rects origins should be centered
    static sf::Vector2f GetOverlapArea(const sf::Vector2f posA, const sf::Vector2f sizeA, const sf::Vector2f posB, const sf::Vector2f sizeB)
    {
        const auto halfWidthA = sizeA.x/2;
        const auto halfHeightA = sizeA.y/2;
        const auto halfWidthB = sizeB.x/2;
        const auto halfHeightB = sizeB.y/2;
        const float dx = abs(posA.x - posB.x);
        const float dy = abs(posA.y - posB.y);
        const auto overlapArea = sf::Vector2f(halfWidthA + halfWidthB - dx, halfHeightA + halfHeightB - dy);
        return overlapArea;
    }

    static sf::Vector2f GetPosResolutionPosition(sf::Vector2f pos, sf::Vector2f pPos, sf::Vector2f overlap, sf::Vector2f pOverlap)
    {
        sf::Vector2f resolutionVec;

        if(pOverlap.y > 0)
        {
            // move in x direction to resolve the collision
            if (pos.x > pPos.x)
            {
                resolutionVec = sf::Vector2f(pos.x - overlap.x, pos.y);
                // trP->SetPos(trP->GetPos().x - overlapArea.x, trP->GetPos().y);
            }
            else
            {
                resolutionVec = sf::Vector2f(pos.x + overlap.x, pos.y);
                // trP->SetPos(trP->GetPos().x + overlapArea.x, trP->GetPos().y);
            }
        }
        if(pOverlap.x > 0)
        {
            // move in y direction to resolve the collision
            if (pos.y > pPos.y)
            {
                resolutionVec = sf::Vector2f(pos.x, pos.y - overlap.y);
                // trP->SetPos(trP->GetPos().x, trP->GetPos().y  - overlapArea.y);
            }
            else
            {
                resolutionVec = sf::Vector2f(pos.x, pos.y + overlap.y);
                // trP->SetPos(trP->GetPos().x, trP->GetPos().y  + overlapArea.y);
            }
        }

        return resolutionVec;
    }
};
