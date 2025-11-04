#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "SickCell.h"
#include "NormalCell.h"
#include "Organism.h"
#include "../Settings.h"

using namespace sf;

Organism::Organism()
{
    cells = {};
    for (int y = 0; y < Settings::sizeY; y++)
    {
        vector<Cell*> row;
        for (int x = 0; x < Settings::sizeX; x++)
        {
            row.push_back(new NormalCell());
        }
        cells.push_back(row);
    }
    cells[7][7] = new SickCell(this, Vector2i(7,7));
    newCells = cells;
}

void Organism::drawGrid(RenderWindow *window)
{
    Vector2u size = window->getSize();
    for (int y = 0; y < Settings::sizeY; y++)
    {
        for (int x = 0; x < Settings::sizeX; x++)
        {
            RectangleShape shape({Settings::gridSize, Settings::gridSize});
            shape.setPosition(x * Settings::gridSize + (x + 1) * Settings::padding, y * Settings::gridSize + (y + 1) * Settings::padding);
            shape.setFillColor(cells[y][x]->getColor());
            window->draw(shape);
        }
    }
}

void Organism::tick()
{
    for (int y = 0; y < Settings::sizeY; y++)
    {
        for (int x = 0; x < Settings::sizeX; x++)
        {
            cells[y][x]->tick();
        }
    }
    cells = newCells;
}

void Organism::editCell(Vector2i position, Cell *newState)
{
    if (position.x < 0 || position.x >= Settings::sizeX || position.y < 0 || position.y >= Settings::sizeY)
        return;
    newCells[position.y][position.x] = newState;
}

bool Organism::canInfect(Vector2i position) const
{
    if (position.x < 0 || position.x >= Settings::sizeX || position.y < 0 || position.y >= Settings::sizeY)
        return false;
    return dynamic_cast<NormalCell*>(cells[position.y][position.x]);
}