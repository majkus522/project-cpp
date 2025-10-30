#ifndef PROJECT_CPP_ORGANISM_H
#define PROJECT_CPP_ORGANISM_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cell.h"

using namespace sf;
using namespace std;

class Organism
{
    public:
        Organism();
        void drawGrid(RenderWindow *window);
        void tick();
        void editCell(Vector2i position, Cell *newState);

    private:
        float gridSize = 30.f;
        float padding = 5.f;
        vector<vector<Cell*>> cells;
        vector<vector<Cell*>> newCells;
};

#endif