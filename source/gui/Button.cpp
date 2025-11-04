#include "Button.h"

Button::Button()
{
    setSize(sf::Vector2f(100, 50));
    setFillColor(Color::Blue);
    setOutlineColor(sf::Color::Red);
    setOutlineThickness(5);
    setPosition(10, 20);
}

bool Button::isClicked(Vector2f position)
{
    return getGlobalBounds().contains(position);
}