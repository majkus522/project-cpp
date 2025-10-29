#ifndef PROJECT_CPP_CELL_H
#define PROJECT_CPP_CELL_H

#include <SFML/Graphics.hpp>
#include "ColorGradient.h"

using namespace sf;

class Cell
{
    protected:
        int state;
        int maxState;
        ColorGradient gradient = ColorGradient(Color::White, Color::White);

    public:
        Cell();
        Color getColor();
        virtual void tick() = 0;
};

#endif