#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "SickCell.h"
#include "NormalCell.h"
#include "Organism.h"
#include <cmath>
#include <iostream>
#include "../Settings.h"

using namespace sf;
using namespace std;

unsigned int Organism::calcSize(int a)
{
    return a * Settings::gridSize + (a + 1) * Settings::padding;
}

Organism::Organism(Vector2i size, RenderWindow* window) : size(size), window(window)
{
    cells = {};
    for (int y = 0; y < size.y; y++)
    {
        vector<Cell*> row;
        for (int x = 0; x < size.x; x++)
        {
            row.push_back(new NormalCell());
        }
        cells.push_back(row);
    }
    cells[ceil(size.y / 2)][ceil(size.x / 2)] = new SickCell(this);
    newCells = cells;
}

void Organism::drawGrid()
{
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
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
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            cells[y][x]->tick({x, y});
        }
    }
    cells = newCells;
}

void Organism::editCell(Vector2i position, Cell *newState)
{
    if (position.x < 0 || position.x >= size.x || position.y < 0 || position.y >= size.y)
        return;
    newCells[position.y][position.x] = newState;
}

bool Organism::canInfect(Vector2i position) const
{
    if (position.x < 0 || position.x >= size.x || position.y < 0 || position.y >= size.y)
        return false;
    return dynamic_cast<NormalCell*>(cells[position.y][position.x]);
}

void Organism::resize(Vector2i newSize)
{
    int diffX = floor((newSize.x - size.x) / 2);
    int diffY = floor((newSize.y - size.y) / 2);
    newCells = {};
    for (int y = 0; y < newSize.y; y++)
    {
        vector<Cell*> row;
        for (int x = 0; x < newSize.x; x++)
        {
            row.push_back(new NormalCell());
        }
        newCells.push_back(row);
    }
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            if (x + diffX < 0 || x + diffX >= newSize.x || y + diffY < 0 || y + diffY >= newSize.y)
                continue;
            newCells[y + diffY][x + diffX] = cells[y][x];
        }
    }
    cells = newCells;
    size = newSize;
}