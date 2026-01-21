#ifndef PROJECT_CPP_INPUTFIELD_H
#define PROJECT_CPP_INPUTFIELD_H

#include <string>
#include "Clickable.h"
#include "GuiElement.h"

using namespace sf;
using namespace std;

class InputField : public GuiElement, public Clickable
{
    protected:
        string text;
        Rect<float> rect;
        void draw(RenderTarget& target, RenderStates states) const override;
        bool focused;

    public:
        InputField(Vector2f position, Vector2f size, void (*function)(const GuiElement*));
        void click(Vector2f position) const override;
        virtual bool setText(string text);
        string getText();
        void setFocus(bool value);
};

#endif