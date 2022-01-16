#include <SFML/Graphics.hpp>
#include <vector>
#include "abymat.h"
#include <iostream>
std::vector<sf::CircleShape> cs;


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "sfml");

    std::vector<sf::CircleShape> points;

    AbyMat::GR graphics;
    AbyMat::Point2D P0(300,300);
    AbyMat::Point2D P1(400,400);
    AbyMat::Point2D P2(300,500);

    for (double i = 0; i < 1; i += 0.02)
    {
        AbyMat::Point2D BezierPoint = graphics.quad_bezier(P0, P1, P2, i);
        std::cout << BezierPoint.getX() << " | " << BezierPoint.getY() << std::endl;
        sf::CircleShape point(5);
        point.setFillColor(sf::Color::Green);
        point.setPosition(sf::Vector2f(BezierPoint.getX(), BezierPoint.getY()));
        points.push_back(point);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        for (int x = 0; x < points.size(); x++)
            window.draw(points[x]);
        window.display();
    }

    return 0;
}