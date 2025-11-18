#ifndef PROJECT_CPP_CLICKABLE_H
#define PROJECT_CPP_CLICKABLE_H

#include "GuiElement.h"

class Clickable
{
    protected:
        void (*function)(const GuiElement*);

    public:
        virtual void click(Vector2f position) const = 0;
};

#endif