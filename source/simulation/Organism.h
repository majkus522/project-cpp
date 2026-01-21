#ifndef PROJECT_CPP_ORGANISM_H
#define PROJECT_CPP_ORGANISM_H

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Organism
{
    public:
        Organism(Vector2i size);
        void drawGrid(RenderWindow& window);
        void tick();
        void resize(Vector2i newSize);
        static unsigned int calcSize(int a);

    private:
        vector<vector<int>> cells;
        vector<vector<int>> newCells;
        Vector2i size;
};

#endif