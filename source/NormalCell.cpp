#include "NormalCell.h"
#include "Cell.h"
#include "ColorGradient.h"

#include <iostream>
using namespace std;

NormalCell::NormalCell()
{
    this->maxState = 3;
    this->state = 3;
    this->gradient = ColorGradient(Color::Blue, Color::Blue);
}

void NormalCell::tick()
{
    cout << "normal" << endl;
}