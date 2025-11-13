#ifndef PROJECT_CPP_BUTTON_H
#define PROJECT_CPP_BUTTON_H

#include "GuiElement.h"

using namespace sf;
using namespace std;

class Button : public GuiElement
{
    protected:
        string text;
        Rect<float> rect;
        void draw(RenderTarget& target, RenderStates states) const override;

    public:
        Button(Vector2f position, Vector2f size, string text);
        bool isClicked(Vector2f position) const;
};

#endif