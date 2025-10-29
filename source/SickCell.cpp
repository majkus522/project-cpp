#include "SickCell.h"
#include "Cell.h"
#include "ColorGradient.h"

#include <iostream>

#include "Settings.h"
using namespace std;

SickCell::SickCell()
{
    this->state = 0;
    this->maxState = Settings::timeSick;
    this->gradient = ColorGradient(Settings::colorNormal, Settings::colorSick);
}

void SickCell::tick()
{
    this->state += 1;
    if (this->state >= maxState)
        cout << "cure" << endl;
}