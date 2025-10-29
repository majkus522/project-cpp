#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include "ColorGradient.h"
#include "Cell.h"
#include "SickCell.h"
#include "NormalCell.h"
#include "Organism.h"
#include "Settings.h"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "SFML works!");
    Organism organism;
    organism.drawGrid(&window);
    Clock clock;
    clock.restart();
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();
        if(clock.getElapsedTime() < Settings::delay)
            continue;
        clock.restart();
        organism.tick();
        organism.drawGrid(&window);
    }
    return 0;
}