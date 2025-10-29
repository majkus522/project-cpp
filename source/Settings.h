#ifndef PROJECT_CPP_SETTINGS_H
#define PROJECT_CPP_SETTINGS_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>

using namespace sf;

class Settings
{
    public:
        static int sizeX;
        static int sizeY;
        static int timeSick;
        static int timeResistant;
        static Time delay;
        static Color colorNormal;
        static Color colorSick;
        static Color colorResistant;
};

#endif