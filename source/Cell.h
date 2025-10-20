#ifndef PROJECT_CPP_CELL_H
#define PROJECT_CPP_CELL_H

#include <SFML/Graphics.hpp>
#include "ColorGradient.h"

using namespace sf;

class Cell
{
    private:
        int state;
        int maxState = 8;
        ColorGradient gradient = ColorGradient(Color::Red, Color::Blue);

    public:
        Cell();
        Cell(int state);
        Color getColor();
};

#endif