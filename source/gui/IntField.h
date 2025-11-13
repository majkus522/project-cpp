#ifndef PROJECT_CPP_NUMBERFIELD_H
#define PROJECT_CPP_NUMBERFIELD_H

#include "InputField.h"

class IntField : public InputField
{
    private:
        int min;
        int max;

    public:
        IntField(Vector2f position, Vector2f size, int min, int max);
        void setText(string text) override;
};

#endif