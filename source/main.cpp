#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "Settings.h"
#include "gui/Button.h"
#include "gui/InputField.h"
#include "gui/IntField.h"
#include "simulation/Organism.h"
#include <map>
#include <string>

using namespace sf;

map<string, GuiElement*> guiElements;
bool isRunning = false;
Organism *organism;
Clock timer;
InputField *focus = nullptr;
RenderWindow* simulation = nullptr;

void setEnabledAll(bool value)
{
    for (pair element : guiElements)
        element.second->setEnabled(value);
}

void createSimulation(const GuiElement * element)
{
    guiElements["buttonStart"]->setEnabled(true);
    Settings::sizeX = ((IntField*)guiElements["fieldSizeX"])->getValue();
    Settings::sizeY = ((IntField*)guiElements["fieldSizeY"])->getValue();
    organism = new Organism();
    if (simulation != nullptr)
        simulation->close();
    simulation = new RenderWindow(VideoMode(Settings::sizeX * Settings::gridSize + (Settings::sizeX + 1) * Settings::padding, Settings::sizeY * Settings::gridSize + (Settings::sizeY + 1) * Settings::padding), "Simulation", sf::Style::Titlebar | sf::Style::Close);
}

void startSimulation(const GuiElement * element)
{
    isRunning = true;
    setEnabledAll(false);
    guiElements["buttonStop"]->setEnabled(true);
    timer.restart();
}

void stopSimulation(const GuiElement * element)
{
    isRunning = false;
    setEnabledAll(true);
    guiElements["buttonStop"]->setEnabled(false);
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
    RenderWindow window(VideoMode(500, 800), "Simulation - Config", sf::Style::Titlebar | sf::Style::Close);
    timer.restart();

    guiElements.insert({"buttonStart", new Button({100, 100}, {200, 50}, "Start", startSimulation)});
    guiElements["buttonStart"]->setEnabled(false);
    guiElements.insert({"buttonStop", new Button({100, 200}, {200, 50}, "Stop", stopSimulation)});
    guiElements["buttonStop"]->setEnabled(false);
    guiElements.insert({"buttonTick", new Button({100, 300}, {200, 50}, "Tick", tick)});
    guiElements.insert({"fieldSizeX", new IntField({100, 400}, {200, 50}, -1000, 1000, setFocus, 15)});
    guiElements.insert({"fieldSizeY", new IntField({100, 450}, {200, 50}, -1000, 1000, setFocus, 15)});
    guiElements.insert({"buttonCreate", new Button({100, 550}, {200, 50}, "Create", createSimulation)});
    bool lockClick = false;
    bool lockInput = false;

    while (window.isOpen())
    {
        //Check events
        Event event;
        window.pollEvent(event);
        if (event.type == Event::Closed)
        {
            window.close();
            if (simulation != nullptr)
                simulation->close();
        }
        else if (event.type == Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == Mouse::Left && !lockClick)
            {
                lockClick = true;
                Vector2i localPosition = Mouse::getPosition(window);
                for (pair element : guiElements)
                {
                    if (dynamic_cast<Clickable*>(element.second))
                    {
                        if (dynamic_cast<Button*>(element.second))
                            ((Button*)element.second)->click((Vector2f)localPosition);
                        else if (dynamic_cast<InputField*>(element.second))
                            ((InputField*)element.second)->click((Vector2f)localPosition);
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

        //Tick simulation
        if(timer.getElapsedTime() >= Settings::delay && isRunning)
            tick(nullptr);

        //Redraw window
        window.clear();
        if (simulation != nullptr)
            simulation->clear();
        if (simulation != nullptr)
            organism->drawGrid(simulation);
        for (pair element : guiElements)
            window.draw(*element.second);
        window.display();
        if (simulation != nullptr)
            simulation->display();
    }
    return 0;
}