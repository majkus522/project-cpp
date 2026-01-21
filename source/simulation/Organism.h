#ifndef PROJECT_CPP_ORGANISM_H
#define PROJECT_CPP_ORGANISM_H

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Organism : public Drawable
{
    public:
        Organism(Vector2i size);
        void tick();
        void resize(Vector2i newSize);
        static unsigned int calcSize(int a);

    private:
        vector<vector<int>> cells;
        vector<vector<int>> newCells;
        Vector2i size;
        void draw(RenderTarget& target, RenderStates states) const;
};

#endif