#pragma once
#include <SFML/Graphics.hpp>

#include "Ball.h"
#include "Paddle.h"
#include "AABB.h"
#include "Tile.h"

class Demo
{
public:
    sf::RenderWindow window;
    Paddle paddle;
    Ball ball;
    sf::Rect<float> screenRect;
    int paddleInput;
    bool isPaused;
    sf::Vector2f postResPos;
    std::vector<Tile> tiles;

    Demo()
        :window(sf::VideoMode(800, 600), "Demo")
    {
        window.setFramerateLimit(60);
        screenRect = sf::Rect<float>(0,0,800,600);
        paddleInput = 0;
        isPaused = false;
        postResPos = sf::Vector2f(0,0);

        sf::Vector2f pos(0,0);

        for (int w = 1; w < 13; ++w)
        {
            for (int h = 1; h < 7; ++h)
            {
                Tile t;
                t.SetPos(pos.x + (t.GetShape().getSize().x + 10) * w, pos.y + (t.GetShape().getSize().y + 10) * h);
                tiles.push_back(t);
            }
        }
    }

    void Run()
    {
        while (window.isOpen())
        {
            Input();
            ball.Move();
            ball.ReboundIfExceedBoundary(screenRect);

            paddle.Move(paddleInput);
            PaddleBallInteraction();
            BallTilesInteraction();

            Render();
        }
    }
private:
    void Input()
    {

        sf::Event event {};
        while (window.pollEvent(event))
        {
#pragma region CloseWindow
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                if(event.key.code == sf::Keyboard::Escape)
                    window.close();
#pragma endregion
#pragma region PaddleInput
            if (event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::A)
                {
                    paddleInput = -1;
                }
                if(event.key.code == sf::Keyboard::D)
                {
                    paddleInput = 1;
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::A)
                {
                    paddleInput = 0;
                }
                if(event.key.code == sf::Keyboard::D)
                {
                    paddleInput = 0;
                }
            }
#pragma endregion
            if (event.type == sf::Event::KeyPressed)
                if(event.key.code == sf::Keyboard::Space)
                    UnPause();
            if (event.type == sf::Event::KeyPressed)
                if(event.key.code == sf::Keyboard::F)
                    ball.SetPos(postResPos);
        }
    }

    void Render()
    {
        window.clear(sf::Color(25, 35,25));

        window.draw(paddle.GetShape());
        window.draw(ball.GetShape());
        for (auto& t:tiles)
            if(!t.IsDestroyed())
                window.draw(t.GetShape());
        // if(tiles[0].IsDestroyed() == false) window.draw(tiles[0].GetShape());

        window.display();
    }

    void UnPause()
    {
        ball.UnPause();
        paddle.UnPause();
        isPaused = false;
    }

    void Pause()
    {
        isPaused = true;
        paddleInput = 0;
        ball.Pause();
        paddle.Pause();
    }

    void PaddleBallInteraction()
    {
        const auto overlap = AABB::GetOverlapArea
            (
                paddle.GetShape().getPosition(), paddle.GetShape().getSize(),
                ball.GetShape().getPosition(), ball.GetShape().getSize()
            );

        if(overlap.x > 0 && overlap.y > 0)
        {
            const auto previousOverlap = AABB::GetOverlapArea
            (
                paddle.GetPreviousPos(), paddle.GetShape().getSize(),
                ball.GetPreviousPos(), ball.GetShape().getSize()
            );

            const auto postResolutionPos = AABB::GetPostResolutionBallPosition
            (
                ball.GetShape().getPosition(),
                ball.GetPreviousPos(),
                paddle.GetShape().getPosition(),
                overlap, previousOverlap
            );

            ball.SetPos(postResolutionPos);

            if(paddle.GetShape().getPosition().y - paddle.GetShape().getSize().y / 2 > ball.GetShape().getPosition().y)
            {
                ball.ReboundY();
            }
            else
            {
                if(ball.GetVelocity().x < .1f && ball.GetVelocity().x > -.1f)
                {
                    ball.AddVel(3,0);
                }
                if(ball.GetShape().getPosition().x > paddle.GetShape().getPosition().x)
                {
                    if (ball.GetVelocity().x < 0)
                        ball.ReboundX();
                }
                else
                {
                    if (ball.GetVelocity().x > 0)
                        ball.ReboundX();
                }
            }
        }
    }

    void BallTilesInteraction()
    {
        for (auto& tile : tiles)
        {
            if(tile.IsDestroyed()) continue;
            const auto overlap = AABB::GetOverlapArea
                (
                    tile.GetShape().getPosition(), tile.GetShape().getSize(),
                    ball.GetShape().getPosition(), ball.GetShape().getSize()
                );

            if(overlap.x > 0 && overlap.y > 0)
            {
                const auto ballPos = ball.GetShape().getPosition();
                const auto ballPrePos = ball.GetPreviousPos();
                const auto ballSize = ball.GetShape().getSize();
                const auto tilePos = tile.GetShape().getPosition();
                const auto tileSize = tile.GetShape().getSize();

                if (ballPrePos.y > tilePos.y + tileSize.y / 2)
                {
                    ball.ReboundY();
                }

                if (ballPrePos.y < tilePos.y - tileSize.y / 2)
                {
                    ball.ReboundY();
                }
                // ball is coming from left and collide with right side of thile
                if(ball.GetPreviousPos().x > tilePos.x + tileSize.x / 2)
                {
                    ball.ReboundX();
                }

                // ball is coming from right and collide with left side of thile
                if(ball.GetPreviousPos().x < tilePos.x - tileSize.x / 2)
                {
                    ball.ReboundX();
                }

                tile.Destroy();
                break;
            }
        }
    }
};
