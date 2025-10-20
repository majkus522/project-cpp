#include <SFML/Graphics.hpp>
#include "ColorGradient.h"
#include "Cell.h"

using namespace sf;

Cell::Cell() {}

Cell::Cell(int state)
{
    this->state = state % maxState;
}

Color Cell::getColor()
{
    return gradient.getColor((float)state / (float)maxState);
}