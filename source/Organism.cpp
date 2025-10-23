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

using namespace std;
using namespace sf;

Organism::Organism(int n)
{
    this->n = n;
    cells = new Cell*[n];
    for (int y = 0; y < n; y++)
    {
        cells[y] = (Cell*)(malloc(sizeof(Cell) * n));
        for (int x = 0; x < n; x++)
        {
            cells[y][x] = NormalCell();
        }
    }
    cells[7][7] = SickCell();
}

void Organism::drawGrid(RenderWindow *window)
{
    window->clear();
    Vector2u size = window->getSize();
    for (int y = 0; y * gridSize + (y + 1) * padding < size.y & y < n; y++)
    {
        for (int x = 0; x * gridSize + (x + 1) * padding < size.x & x < n; x++)
        {
            RectangleShape shape({gridSize, gridSize});
            shape.setPosition(x * gridSize + (x + 1) * padding, y * gridSize + (y + 1) * padding);
            shape.setFillColor(cells[y][x].getColor());
            window->draw(shape);
        }
    }
    window->display();
}