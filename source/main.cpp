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

vector<GuiElement*> guiElements;
bool isRunning = false;
Organism *organism;
Clock timer;
InputField *focus = nullptr;

void setEnabledAll(bool value)
{
    for (GuiElement * element : guiElements)
        element->setEnabled(value);
}

void startSimulation(const GuiElement * element)
{
    isRunning = true;
    setEnabledAll(false);
    guiElements[1]->setEnabled(true);
    timer.restart();
}

void stopSimulation(const GuiElement * element)
{
    isRunning = false;
    setEnabledAll(true);
    guiElements[1]->setEnabled(false);
}

void setFocus(const GuiElement * element)
{
    focus = (InputField*)element;
}

void tick(const GuiElement * element)
{
    organism->tick();
    timer.restart();
}

int main()
{
    RenderWindow window(VideoMode(500, 800), "Simulation - Config");
    RenderWindow simulation(VideoMode(Settings::sizeX * Settings::gridSize + (Settings::sizeX + 1) * Settings::padding, Settings::sizeY * Settings::gridSize + (Settings::sizeY + 1) * Settings::padding), "Simulation");
    timer.restart();
    organism = new Organism();

    guiElements.push_back(new Button({100, 100}, {200, 50}, "Start", startSimulation));
    guiElements.push_back(new Button({100, 200}, {200, 50}, "Stop", stopSimulation));
    guiElements[1]->setEnabled(false);
    guiElements.push_back(new Button({100, 300}, {200, 50}, "Tick", tick));
    guiElements.push_back(new IntField({100, 400}, {200, 50}, -1000, 1000, setFocus));
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

        if (event.type == Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == Mouse::Left && !lockClick)
            {
                lockClick = true;
                Vector2i localPosition = Mouse::getPosition(window);
                for (GuiElement * element : guiElements)
                {
                    if (dynamic_cast<Clickable*>(element))
                    {
                        if (dynamic_cast<Button*>(element))
                            ((Button*)element)->click((Vector2f)localPosition);
                        else if (dynamic_cast<InputField*>(element))
                            ((InputField*)element)->click((Vector2f)localPosition);
                    }
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
            tick(nullptr);
        }
        organism->drawGrid(&simulation);
        for (GuiElement * element : guiElements)
            window.draw(*element);
        window.display();
        simulation.display();
    }
    return 0;
}