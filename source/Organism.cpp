#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include "ColorGradient.h"
#include "Cell.h"
#include "SickCell.h"
#include "NormalCell.h"
#include "Organism.h"
#include "Settings.h"

using namespace std;
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
    window->clear();
    Vector2u size = window->getSize();
    for (int y = 0; y * gridSize + (y + 1) * padding < size.y & y < Settings::sizeY; y++)
    {
        for (int x = 0; x * gridSize + (x + 1) * padding < size.x & x < Settings::sizeX; x++)
        {
            RectangleShape shape({gridSize, gridSize});
            shape.setPosition(x * gridSize + (x + 1) * padding, y * gridSize + (y + 1) * padding);
            shape.setFillColor(cells[y][x]->getColor());
            window->draw(shape);
        }
    }
    window->display();
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

void Organism::infect(Vector2i position)
{
    if (position.x < 0 || position.x >= Settings::sizeX || position.y < 0 || position.y >= Settings::sizeY)
        return;
    newCells[position.y][position.x] = new SickCell(this, position);
}