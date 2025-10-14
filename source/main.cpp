#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    sf::CircleShape shape(100.f, 6);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(sf::Vector2f(0, 0));

    sf::CircleShape shape1(100.f, 6);
    shape1.setFillColor(sf::Color::Red);
    shape1.setPosition(sf::Vector2f(100, 300));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.draw(shape1);
        window.display();
    }
    return 0;
}