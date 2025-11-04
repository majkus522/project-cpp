#ifndef PROJECT_CPP_BUTTON_H
#define PROJECT_CPP_BUTTON_H

#include <SFML/Graphics/RectangleShape.hpp>

using namespace sf;

class Button : public RectangleShape
{
    public:
        Button();
        bool isClicked(Vector2f position);
};

#endif