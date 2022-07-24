#include <SFML/Graphics.hpp>
struct Point {
    int x, y;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(2560, 1440), "SFML", sf::Style::Fullscreen);
    std::vector<sf::CircleShape> shape;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }
        Point p1{ 600,400 };
        Point p2{ 2000,1440 };

        int deltaX = p2.x - p1.x;
        int deltaY = p2.y - p1.y;
        int y = p1.y;
        int p = 2 * deltaY - deltaX;
        for(int i = p1.x; i < p2.x+1; i++){
            if (p < 0) {
                sf::CircleShape pixel(1);
                pixel.setFillColor(sf::Color::Green);
                pixel.setPosition(sf::Vector2f(i + 1, y));
                shape.push_back(pixel);
                p = p + 2 * deltaY;
            }
            else {
                sf::CircleShape pixel(1);
                pixel.setFillColor(sf::Color::Green);
                pixel.setPosition(sf::Vector2f(i + 1, y + 1));
                shape.push_back(pixel);
                p = p + (2 * deltaY) - (2 * deltaX);
                y++;
            }
        }

        window.clear();
        for(auto x : shape)
            window.draw(x);
        window.display();
    }

    return 0;
}