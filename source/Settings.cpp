#include <SFML/System/Time.hpp>
#include "Settings.h"

using namespace sf;

int Settings::sizeX = 15;
int Settings::sizeY = 15;
int Settings::timeSick = 6;
int Settings::timeResistant = 2;
float Settings::spreadChance = 0.5f;
float Settings::gridSize = 30.f;
float Settings::padding = 5.f;
Time Settings::delay = seconds(0.25f);
Color Settings::colorNormal = Color::White;
Color Settings::colorSick = Color::Red;
Color Settings::colorResistant = Color::Green;