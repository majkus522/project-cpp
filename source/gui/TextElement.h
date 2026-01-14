#ifndef PROJECT_CPP_TEXT_ELEMENT_H
#define PROJECT_CPP_TEXT_ELEMENT_H

#include "GuiElement.h"

using namespace sf;
using namespace std;

class TextElement : public GuiElement
{
    protected:
        string text;
        Rect<float> rect;
        void draw(RenderTarget& target, RenderStates states) const override;
        Font font;

    public:
        TextElement(Vector2f position, Vector2f size, string text);
};

#endif