#include <SFML/System/Time.hpp>
#include "Settings.h"

using namespace sf;

int Settings::timeSick = 6;
int Settings::timeResistant = 2;
float Settings::spreadChance = 0.5f;
unsigned int Settings::gridSize = 3;
Time Settings::delay = seconds(1);
Color Settings::colorNormal = Color::White;
ColorGradient Settings::colorSick = ColorGradient(Color::Red, Color(0, 0, 0));
ColorGradient Settings::colorResistant = ColorGradient(Color::Green, Color::White);