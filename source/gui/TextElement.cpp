#include <string>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "TextElement.h"

using namespace sf;
using namespace std;

TextElement::TextElement(Vector2f position, Vector2f size, string text)
{
    this->position = position;
    this->size = size;
    this->text = text;
    this->rect = Rect<float>(position, size);
    font.loadFromFile("arial.ttf");
}

void TextElement::draw(RenderTarget& target, RenderStates states) const
{
    Text textShape = Text(text, font);
    FloatRect textBounds = textShape.getLocalBounds();
    textShape.setOrigin(textBounds.left, textBounds.top + textBounds.height / 2.0f);
    Vector2f rectCenter(rect.getPosition().x, rect.getPosition().y + rect.getSize().y / 2.0f);
    textShape.setPosition(rectCenter);
    textShape.setCharacterSize(30);
    textShape.setFillColor(Color::Red);
    target.draw(textShape, states);
}