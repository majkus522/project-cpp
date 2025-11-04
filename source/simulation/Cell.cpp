#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "../ColorGradient.h"

using namespace sf;

Cell::Cell()
{
    this->state = 0;
    this->maxState = 1;
}

Color Cell::getColor()
{
    return this->gradient.getColor((float)state / (float)maxState);
}