#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include "ColorGradient.h"
#include "Cell.h"
#include "SickCell.h"
#include "NormalCell.h"

using namespace std;
using namespace sf;

float gridSize = 30.f;
float padding = 5.f;
const int n = 15;

void drawGrid(RenderWindow *window, Cell **cells)
{
	cout << "d" << endl;
    window->clear();
	cout << "d" << endl;
    Vector2u size = window->getSize();
	cout << cells[7][7].state << endl;
    for (int y = 0; y * gridSize + (y + 1) * padding < size.y & y < n; y++)
    {
        for (int x = 0; x * gridSize + (x + 1) * padding < size.x & x < n; x++)
        {
			cout << "a" << endl;
            RectangleShape shape({gridSize, gridSize});
			cout << "a" << endl;
            shape.setPosition(x * gridSize + (x + 1) * padding, y * gridSize + (y + 1) * padding);
			cout << "a" << endl;
            shape.setFillColor(cells[y][x].getColor());
			cout << "a" << endl;
            window->draw(shape);
			cout << "a" << endl;
        }
    }
    window->display();
	cout << "d" << endl;
}

int main()
{
	cout << "k" << endl;
    RenderWindow window(VideoMode::getDesktopMode(), "SFML works!");
	cout << "k" << endl;
    Cell **cells = new Cell*[n];
	cout << "k" << endl;
    for (int y = 0; y < n; y++)
    {
		cells[y] = (Cell*)malloc(sizeof(Cell) * n);
        for (int x = 0; x < n; x++)
        {
            cells[y][x] = NormalCell();
        }
    }
	cout << "k" << endl;
    cells[7][7] = SickCell();
	cout << "k" << endl;
    drawGrid(&window, cells);
	cout << "k" << endl;
    Clock clock;
    Time delay = seconds(5);
    clock.restart();
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();
        if(clock.getElapsedTime() < delay)
            continue;
        clock.restart();
        drawGrid(&window, cells);
    }
    return 0;
}