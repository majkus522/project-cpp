#include <random>
#include "SickCell.h"
#include "Cell.h"
#include "ResistantCell.h"
#include "../ColorGradient.h"
#include "../Settings.h"

float randomFloat()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(gen);
}

SickCell::SickCell(Organism *parent)
{
    this->organism = parent;
    this->state = 0;
    this->maxState = Settings::timeSick;
    this->gradient = ColorGradient(Settings::colorSick, Settings::colorSick);
}

void SickCell::tick(Vector2i position)
{
    this->state += 1;
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            if (x != 0 || y != 0)
                if (organism->canInfect(position + Vector2i(x, y)))
                    if (randomFloat() < Settings::spreadChance)
                        organism->editCell(position + Vector2i(x, y), new SickCell(organism));
        }
    }
    if (state >= maxState)
    {
        organism->editCell(position, new ResistantCell(organism));
    }
}