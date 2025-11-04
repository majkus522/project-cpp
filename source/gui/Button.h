#ifndef PROJECT_CPP_BUTTON_H
#define PROJECT_CPP_BUTTON_H

#include <SFML/Graphics/RectangleShape.hpp>

using namespace sf;
using namespace std;

class Button : public Drawable
{
    private:
        Vector2f position;
        Vector2f size;
        string text;
        Rect<float> rect;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    public:
        Button(Vector2f position, Vector2f size, string text);
        bool isClicked(Vector2f position) const;
};

#endif