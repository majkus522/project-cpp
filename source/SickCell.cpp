#include "SickCell.h"
#include "Cell.h"
#include "ColorGradient.h"

#include <iostream>
#include <random>

#include "Settings.h"
using namespace std;

float randomFloat()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(gen);
}

SickCell::SickCell(Organism *parent, Vector2i position)
{
    this->organism = parent;
    this->position = position;
    this->state = 0;
    this->maxState = Settings::timeSick;
    this->gradient = ColorGradient(Settings::colorSick, Settings::colorSick);
}

void SickCell::tick()
{
    this->state += 1;
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            if (x != 0 || y != 0)
                if (randomFloat() < Settings::spreadChance)
                    organism->editCell(position + Vector2i(x, y), new SickCell(organism, position + Vector2i(x, y)));
        }
    }
}