#include "SickCell.h"
#include "Cell.h"
#include "ColorGradient.h"

#include <iostream>
using namespace std;

SickCell::SickCell()
{
    this->maxState = 4;
    this->state = 4;
    this->gradient = ColorGradient(Color::Red, Color::Red);
}

void SickCell::tick()
{
    cout << "sick" << endl;
}