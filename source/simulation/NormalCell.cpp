#include "NormalCell.h"
#include "Cell.h"

NormalCell::NormalCell()
{
    this->maxState = 3;
    this->state = 3;
}

void NormalCell::tick(Vector2i position) { }