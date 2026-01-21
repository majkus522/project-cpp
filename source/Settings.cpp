#include <SFML/System/Time.hpp>
#include "Settings.h"

using namespace sf;

int Settings::timeSick = 6;
int Settings::timeResistant = 2;
float Settings::padding = 0.f;
float Settings::spreadChance = 0.5f;
float Settings::gridSize = 3.f;
Time Settings::delay = seconds(1);
Color Settings::colorNormal = Color::White;
Color Settings::colorSick = Color::Red;
Color Settings::colorResistant = Color::Green;