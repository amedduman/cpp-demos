#pragma once
#include <SFML/Graphics.hpp>

#include "Ball.h"
#include "Paddle.h"
#include "AABB.h"

class Demo
{
public:
    sf::RenderWindow window;
    Paddle paddle;
    Ball ball;
    sf::Rect<float> screenRect;
    int paddleInput;

    Demo()
        :window(sf::VideoMode(800, 600), "Demo")
    {
        window.setFramerateLimit(60);
        screenRect = sf::Rect<float>(0,0,800,600);
        paddleInput = 0;
    }

    void Run()
    {
        while (window.isOpen())
        {
            Input();
            ball.Move();
            ball.ReboundIfExceedBoundary(screenRect);

            paddle.Move(paddleInput);

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
                    ball.GetPeviousPos(), ball.GetShape().getSize()
                );

                const auto postResolutionPos = AABB::GetPosResolutionPosition
                (
                 ball.GetShape().getPosition(),
                ball.GetPeviousPos(),
                     overlap, previousOverlap
                );

                ball.SetPos(postResolutionPos);
                if(overlap.y > 0)
                    ball.ReboundX();
                if(overlap.x > 0)
                    ball.ReboundY();
                // Pause();
            }

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
        }
    }
    void UnPause()
    {
        ball.UnPause();
        paddle.UnPause();
    }
    void Pause()
    {
        paddleInput = 0;
        ball.Pause();
        paddle.Pause();
    }
    void Render()
    {
        window.clear(sf::Color(25, 35,25));

        window.draw(paddle.GetShape());
        window.draw(ball.GetShape());

        window.display();
    }
};
