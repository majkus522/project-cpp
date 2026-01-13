#ifndef PROJECT_CPP_ORGANISM_H
#define PROJECT_CPP_ORGANISM_H

#include <SFML/Graphics.hpp>
#include "Cell.h"

using namespace sf;
using namespace std;

class Organism
{
    public:
        Organism(Vector2i size);
        void drawGrid(RenderWindow *window);
        void tick();
        void editCell(Vector2i position, Cell *newState);
        bool canInfect(Vector2i position) const;

    private:
        vector<vector<Cell*>> cells;
        vector<vector<Cell*>> newCells;
        Vector2i size;
};

#endif