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
    int paddleDeltaMoveX;

    Demo()
        :window(sf::VideoMode(800, 600), "Demo")
    {
        window.setFramerateLimit(60);
        screenRect = sf::Rect<float>(0,0,800,600);
        paddleDeltaMoveX = 0;
    }

    void Run()
    {
        while (window.isOpen())
        {
            Input();
            ball.Move();
            ball.ReboundIfExceedBoundary(screenRect);

            const auto overlap = AABB::GetOverlapArea(paddle.GetShape(), ball.GetShape());
            if(overlap.x > 0 && overlap.y > 0)
            {
                std::cout << "overlap" << std::endl;

                const auto pos = paddle.GetShape().getPosition();
                const auto halfSize = paddle.GetShape().getSize();

                auto paddleRect = sf::Rect<float>(pos.x - halfSize.x, pos.y + halfSize.y, halfSize.x * 2, halfSize.y * 2);
                ball.ReboundIfExceedBoundary(paddleRect);
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
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                if(event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                if(event.key.code == sf::Keyboard::Space)
                {
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {

            }
        }
    }
    void Render()
    {
        window.clear(sf::Color(25, 35,25));

        window.draw(paddle.GetShape());
        window.draw(ball.GetShape());

        window.display();
    }
};
