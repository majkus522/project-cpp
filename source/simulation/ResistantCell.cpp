#include "ResistantCell.h"
#include "NormalCell.h"

ResistantCell::ResistantCell(Organism *parent)
{
    this->organism = parent;
    this->state = 0;
    this->maxState = Settings::timeResistant;
    this->gradient = ColorGradient(Settings::colorResistant, Settings::colorResistant);
}

void ResistantCell::tick(Vector2i position)
{
    this->state += 1;
    if (state >= maxState)
    {
        organism->editCell(position, new NormalCell());
    }
}