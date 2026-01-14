#ifndef PROJECT_CPP_CELL_H
#define PROJECT_CPP_CELL_H

#include <SFML/Graphics.hpp>
#include "../ColorGradient.h"
#include "../Settings.h"

using namespace sf;

class Cell
{
    protected:
        int state;
        int maxState;
        ColorGradient gradient = ColorGradient(Settings::colorNormal, Settings::colorNormal);

    public:
        Cell();
        Color getColor();
        virtual void tick(Vector2i position) = 0;
};

#endif