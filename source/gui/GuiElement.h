#ifndef PROJECT_CPP_GUIELEMENT_H
#define PROJECT_CPP_GUIELEMENT_H

#include <SFML/Graphics/Drawable.hpp>

using namespace sf;

class GuiElement : public Drawable
{
    protected:
        Vector2f position;
        Vector2f size;

    public:
        virtual void draw(RenderTarget& target, RenderStates states) const = 0;
};

#endif