#ifndef PROJECT_CPP_SETTINGS_H
#define PROJECT_CPP_SETTINGS_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include "ColorGradient.h"

using namespace sf;

class Settings
{
    public:
        static int timeSick;
        static int timeResistant;
        static float spreadChance;
        static unsigned int gridSize;
        static Time delay;
        static Color colorNormal;
        static ColorGradient colorSick;
        static ColorGradient colorResistant;
};

#endif