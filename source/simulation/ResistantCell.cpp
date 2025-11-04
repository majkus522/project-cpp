#include "ResistantCell.h"
#include "NormalCell.h"

ResistantCell::ResistantCell(Organism *parent, Vector2i position)
{
    this->organism = parent;
    this->position = position;
    this->state = 0;
    this->maxState = Settings::timeResistant;
    this->gradient = ColorGradient(Settings::colorResistant, Settings::colorResistant);
}

void ResistantCell::tick()
{
    this->state += 1;
    if (state >= maxState)
    {
        organism->editCell(position, new NormalCell());
    }
}