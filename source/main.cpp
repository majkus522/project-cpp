#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "Settings.h"
#include "gui/Button.h"
#include "simulation/Organism.h"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(500, 800), "Simulation - Config");
    RenderWindow simulation(VideoMode(Settings::sizeX * Settings::gridSize + (Settings::sizeX + 1) * Settings::padding, Settings::sizeY * Settings::gridSize + (Settings::sizeY + 1) * Settings::padding), "Simulation");
    Organism organism;
    organism.drawGrid(&window);
    Clock clock;
    clock.restart();
    Button button = Button();
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed) {
                window.close();
                simulation.close();
            }
        while (simulation.pollEvent(event))
            if (event.type == Event::Closed) {
                window.close();
                simulation.close();
            }
        window.clear();
        simulation.clear();
        if(clock.getElapsedTime() < Settings::delay)
            continue;
        window.draw(button);
        clock.restart();
        organism.tick();
        organism.drawGrid(&simulation);
        window.display();
        simulation.display();
    }
    return 0;
}