#include "ColorGradient.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;
using namespace sf;

ColorGradient::ColorGradient(Color start, Color end)
{
    this->start = start;
    deltaR = end.r - start.r;
    deltaG = end.g - start.g;
    deltaB = end.b - start.b;
    deltaA = end.a - start.a;
}

Color ColorGradient::getColor(float percent)
{
    percent = max(0.f, min(percent, 1.f));
    Color color = start;
    color.r = color.r + (int)(deltaR * percent);
    color.g = color.g + (int)(deltaG * percent);
    color.b = color.b + (int)(deltaB * percent);
    color.a = color.a + (int)(deltaA * percent);
    return color;
}