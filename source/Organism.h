#ifndef PROJECT_CPP_ORGANISM_H
#define PROJECT_CPP_ORGANISM_H

#include <SFML/Graphics.hpp>
#include "Cell.h"

using namespace sf;

class Organism
{
    public:
        Organism(int n);
        void drawGrid(RenderWindow *window);

    private:
        int n;
        float gridSize = 30.f;
        float padding = 5.f;
        Cell **cells;
};

#endif