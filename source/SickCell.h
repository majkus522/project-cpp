#ifndef PROJECT_CPP_SICKCELL_H
#define PROJECT_CPP_SICKCELL_H

#include "Cell.h"
#include "Organism.h"

class SickCell : public Cell
{
    private:
        Organism *organism;
        Vector2i position;

    public:
        SickCell(Organism *parent, Vector2i position);
        void tick() override;
};

#endif