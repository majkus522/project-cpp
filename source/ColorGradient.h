#ifndef PROJECT_CPP_COLORGRADIENT_H
#define PROJECT_CPP_COLORGRADIENT_H

#include <SFML/Graphics.hpp>

using namespace sf;

class ColorGradient
{
    private:
        Color start;
        int deltaR;
        int deltaG;
        int deltaB;

    public:
        ColorGradient(Color start, Color end);
        Color getColor(float percent);
};

#endif