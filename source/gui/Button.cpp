#include <string>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Button.h"

using namespace sf;
using namespace std;

Button::Button(Vector2f position, Vector2f size, string text, void (*function)(const GuiElement*))
{
    this->position = position;
    this->size = size;
    this->text = text;
    this->function = function;
    this->rect = Rect<float>(position, size);
    font.loadFromFile("arial.ttf");
}

void Button::click(Vector2f position) const
{
    if (rect.contains(position) && isEnabled)
        function(this);
}

void Button::draw(RenderTarget &target, RenderStates states) const
{
    RectangleShape rectangle;
    rectangle.setPosition(position);
    rectangle.setSize(size);
    rectangle.setFillColor(isEnabled ? Color::White : Color::Black);
    rectangle.setOutlineColor(Color(100, 100, 100));
    rectangle.setOutlineThickness(3);
    target.draw(rectangle, states);

    Text textShape = Text(text, font);
    FloatRect textBounds = textShape.getLocalBounds();
    textShape.setOrigin(textBounds.left + textBounds.width / 2.0f,textBounds.top + textBounds.height / 2.0f);
    Vector2f rectCenter(rect.getPosition().x + rect.getSize().x / 2.0f, rect.getPosition().y + rect.getSize().y / 2.0f);
    textShape.setPosition(rectCenter);
    textShape.setCharacterSize(30);
    textShape.setFillColor(Color::Red);
    target.draw(textShape, states);
}