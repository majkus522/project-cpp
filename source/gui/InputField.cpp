#include <string>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "InputField.h"

using namespace sf;
using namespace std;

InputField::InputField(Vector2f position, Vector2f size)
{
    this->position = position;
    this->size = size;
    this->text = "";
    this->rect = Rect<float>(position, size);
}

bool InputField::isClicked(Vector2f position) const
{
    return rect.contains(position);
}

void InputField::setText(string text)
{
    if ((int)text[0] == 8) {
        this->text = this->text.substr(1);
        return;
    }
    this->text += text;
}

void InputField::draw(RenderTarget &target, RenderStates states) const
{
    RectangleShape rectangle;
    rectangle.setPosition(position);
    rectangle.setSize(size);
    rectangle.setFillColor(Color::White);
    rectangle.setOutlineColor(Color(100, 100, 100));
    rectangle.setOutlineThickness(3);
    target.draw(rectangle, states);

    Font font;
    font.loadFromFile("arial.ttf");
    Text textShape = Text(text, font);
    FloatRect textBounds = textShape.getLocalBounds();
    textShape.setOrigin(textBounds.left - 10,textBounds.top + textBounds.height / 2.0f);
    Vector2f rectCenter(rect.getPosition().x, rect.getPosition().y + rect.getSize().y / 2.0f);
    textShape.setPosition(rectCenter);
    textShape.setCharacterSize(30);
    textShape.setFillColor(Color::Red);
    target.draw(textShape, states);
}