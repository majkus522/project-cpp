#ifndef PROJECT_CPP_BUTTON_H
#define PROJECT_CPP_BUTTON_H

#include "Clickable.h"
#include "GuiElement.h"

using namespace sf;
using namespace std;

class Button : public GuiElement, public Clickable
{
    protected:
        string text;
        Rect<float> rect;
        void draw(RenderTarget& target, RenderStates states) const override;

    public:
        Button(Vector2f position, Vector2f size, string text, void (*function)(const GuiElement*));
        void click(Vector2f position) const override;
};

#endif