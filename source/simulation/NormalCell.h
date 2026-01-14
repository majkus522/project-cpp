#ifndef PROJECT_CPP_NORMALCELL_H
#define PROJECT_CPP_NORMALCELL_H

#include "Cell.h"

class NormalCell : public Cell
{
    public:
        NormalCell();
        void tick(Vector2i position) override;
};

#endif