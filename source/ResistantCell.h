#ifndef PROJECT_CPP_RESISTANTCELL_H
#define PROJECT_CPP_RESISTANTCELL_H

#include "Organism.h"

class ResistantCell : public Cell
{
    private:
        Organism *organism;
        Vector2i position;

    public:
        ResistantCell(Organism *parent, Vector2i position);
        void tick() override;
};

#endif