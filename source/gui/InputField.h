#ifndef PROJECT_CPP_INPUTFIELD_H
#define PROJECT_CPP_INPUTFIELD_H

#include <string>
#include <SFML/Graphics/Drawable.hpp>

using namespace sf;
using namespace std;

class InputField : public Drawable
{
    protected:
        Vector2f position;
        Vector2f size;
        string text;
        Rect<float> rect;
        void draw(RenderTarget& target, RenderStates states) const override;

    public:
        InputField(Vector2f position, Vector2f size);
        bool isClicked(Vector2f position) const;
        virtual void setText(string text);
};

#endif