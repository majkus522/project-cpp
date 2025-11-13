#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "Settings.h"
#include "gui/Button.h"
#include "gui/InputField.h"
#include "gui/IntField.h"
#include "simulation/Organism.h"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(500, 800), "Simulation - Config");
    RenderWindow simulation(VideoMode(Settings::sizeX * Settings::gridSize + (Settings::sizeX + 1) * Settings::padding, Settings::sizeY * Settings::gridSize + (Settings::sizeY + 1) * Settings::padding), "Simulation");
    Organism organism;
    Clock timer;
    timer.restart();
    Button startButton = Button({100, 100}, {200, 50}, "Start");
    Button stopButton = Button({100, 200}, {200, 50}, "Stop");
    Button tickButton = Button({100, 300}, {200, 50}, "Tick");
    IntField field = IntField({100, 400}, {200, 50}, -1000, 1000);
    InputField *focus = nullptr;
    bool isRunning = false;
    bool lockClick = false;
    bool lockInput = false;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
            {
                window.close();
                simulation.close();
            }
        while (simulation.pollEvent(event))
            if (event.type == Event::Closed)
            {
                window.close();
                simulation.close();
            }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left && !lockClick)
            {
                lockClick = true;
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                if (startButton.isClicked((Vector2f)localPosition))
                {
                    isRunning = true;
                }
                else if (stopButton.isClicked((Vector2f)localPosition))
                {
                    isRunning = false;
                }
                else if (tickButton.isClicked((Vector2f)localPosition) && !isRunning)
                {
                    organism.tick();
                }
                else if (field.isClicked((Vector2f)localPosition))
                {
                    focus = &field;
                }
                else
                {
                    focus = nullptr;
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            lockClick = false;
        }
        else if (event.type == Event::TextEntered && !lockInput && focus != nullptr)
        {
            if (event.text.unicode < 128)
            {
                lockInput = true;
                sf::String input = static_cast<char>(event.text.unicode);
                focus->setText(input);
            }
        }
        else if (event.type == Event::KeyReleased)
        {
            lockInput = false;
        }


        window.clear();
        simulation.clear();
        if(timer.getElapsedTime() >= Settings::delay && isRunning)
        {
            organism.tick();
            timer.restart();
        }
        organism.drawGrid(&simulation);
        window.draw(startButton);
        window.draw(stopButton);
        window.draw(tickButton);
        window.draw(field);
        window.display();
        simulation.display();
    }
    return 0;
}