#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <list>
#include "ColorGradient.h"
#include "Cell.h"

using namespace std;
using namespace sf;

int gridSize = 30;
int padding = 5;
int n = 15;

int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "SFML works!");
    Cell cells[n][n] = {};
    list<RectangleShape> grid;
    Vector2u size = window.getSize();
    for (int y = 0; y * gridSize + (y + 1) * padding < size.y & y < n; y++)
    {
        for (int x = 0; x * gridSize + (x + 1) * padding < size.x & x < n; x++)
        {
            cells[y][x] = Cell(x + y);
            RectangleShape shape({gridSize, gridSize});
            shape.setPosition(x * gridSize + (x + 1) * padding, y * gridSize + (y + 1) * padding);
            shape.setFillColor(cells[y][x].getColor());
            grid.push_back(shape);
        }
    }
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        for (RectangleShape shape : grid)
            window.draw(shape);
        window.display();
    }
    return 0;
}