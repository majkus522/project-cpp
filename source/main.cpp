#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "Settings.h"
#include "gui/Button.h"
#include "gui/TextElement.h"
#include "gui/InputField.h"
#include "gui/IntField.h"
#include "simulation/Organism.h"
#include <map>
#include <string>
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

using namespace sf;
using namespace std;

map<string, GuiElement*> guiElements;
bool isRunning = false;
Organism *organism;
Clock timer;
InputField *focus = nullptr;
RenderWindow* simulation = nullptr;

void initSettings()
{
    Settings::timeSick = ((IntField*)guiElements["fieldTimeSick"])->getValue();
    Settings::timeResistant = ((IntField*)guiElements["fieldTimeRes"])->getValue();
    Settings::spreadChance = ((IntField*)guiElements["fieldPercent"])->getValue() / 100.0f;
}

void setEnabledAll(bool value)
{
    for (pair<string, GuiElement*> element : guiElements)
        element.second->setEnabled(value);
}

void createSimulation(const GuiElement * element)
{
    guiElements["buttonStart"]->setEnabled(true);
    guiElements["buttonTick"]->setEnabled(true);
    int x = ((IntField*)guiElements["fieldSizeX"])->getValue();
    int y = ((IntField*)guiElements["fieldSizeY"])->getValue();
    if (simulation != nullptr)
        simulation->close();
    simulation = new RenderWindow(VideoMode(Organism::calcSize(x), Organism::calcSize(y)), "Simulation", sf::Style::Titlebar | sf::Style::Close);
    organism = new Organism({ x, y }, simulation);
    guiElements["buttonCreate"]->setEnabled(false);
    guiElements["buttonResize"]->setEnabled(true);
}

void startSimulation(const GuiElement * element)
{
    initSettings();
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
    guiElements["buttonCreate"]->setEnabled(false);
}

void setFocus(const GuiElement * element)
{
    focus = (InputField*)element;
}

void tick(const GuiElement * element)
{
    initSettings();
    organism->tick();
    timer.restart();
}

void resize(const GuiElement* element)
{
    int x = ((IntField*)guiElements["fieldSizeX"])->getValue();
    int y = ((IntField*)guiElements["fieldSizeY"])->getValue();
    organism->resize({ x, y });
    simulation->close();
    simulation = new RenderWindow(VideoMode(Organism::calcSize(x), Organism::calcSize(y)), "Simulation", sf::Style::Titlebar | sf::Style::Close);
    organism->window = simulation;
}

int main()
{
    RenderWindow window(VideoMode(550, 800), "Simulation - Config", sf::Style::Titlebar | sf::Style::Close);
    timer.restart();

    guiElements.insert({"buttonStart", new Button({50, 50}, {150, 50}, "Start", startSimulation)});
    guiElements["buttonStart"]->setEnabled(false);
    guiElements.insert({"buttonStop", new Button({200, 50}, {150, 50}, "Stop", stopSimulation)});
    guiElements["buttonStop"]->setEnabled(false);
    guiElements.insert({"buttonTick", new Button({350, 50}, {150, 50}, "Tick", tick)});
    guiElements["buttonTick"]->setEnabled(false);

    guiElements.insert({ "textX", new TextElement({50, 150}, {50, 50}, "X:") });
    guiElements.insert({"fieldSizeX", new IntField({100, 150}, {100, 50}, 1, 100, setFocus, 15)});
    guiElements.insert({ "textY", new TextElement({300, 150}, {50, 50}, "Y:") });
    guiElements.insert({"fieldSizeY", new IntField({350, 150}, {100, 50}, 1, 100, setFocus, 15)});

    guiElements.insert({"buttonCreate", new Button({100, 250}, {150, 50}, "Create", createSimulation)});
    guiElements.insert({"buttonResize", new Button({300, 250}, {150, 50}, "Resize", resize)});
    guiElements["buttonResize"]->setEnabled(false);

    guiElements.insert({ "textTimeSick", new TextElement({50, 400}, {150, 50}, "Time sick:") });
    guiElements.insert({ "fieldTimeSick", new IntField({300, 400}, {100, 50}, 1, 100, setFocus, 6) });
    guiElements.insert({ "textTimeRes", new TextElement({50, 450}, {200, 50}, "Time resistant:") });
    guiElements.insert({ "fieldTimeRes", new IntField({300, 450}, {100, 50}, 1, 100, setFocus, 2) });
    guiElements.insert({ "textPercent", new TextElement({50, 500}, {200, 50}, "Spread percent:") });
    guiElements.insert({ "fieldPercent", new IntField({300, 500}, {100, 50}, 1, 100, setFocus, 50) });

    bool lockClick = false;
    bool lockInput = false;

    Event simulationEvent;
    Event windowEvent;

    while (window.isOpen())
    {
        //Check events - simulation
        if (simulation != nullptr)
        {
            simulation->pollEvent(simulationEvent);
            if (simulationEvent.type == Event::Closed)
            {
                simulation->close();
                simulation = nullptr;
                guiElements["buttonStart"]->setEnabled(false);
                guiElements["buttonStop"]->setEnabled(false);
                guiElements["buttonTick"]->setEnabled(false);
                guiElements["buttonCreate"]->setEnabled(true);
                guiElements["buttonResize"]->setEnabled(false);
                guiElements["fieldSizeX"]->setEnabled(true);
                guiElements["fieldSizeY"]->setEnabled(true);
                guiElements["fieldTimeSick"]->setEnabled(true);
                guiElements["fieldTimeRes"]->setEnabled(true);
                guiElements["fieldPercent"]->setEnabled(true);
            }
        }

        //Check events - window
        window.pollEvent(windowEvent);
        if (windowEvent.type == Event::Closed)
        {
            window.close();
            if (simulation != nullptr)
                simulation->close();
        }
        else if (windowEvent.type == Event::MouseButtonPressed)
        {
            if (windowEvent.mouseButton.button == Mouse::Left && !lockClick)
            {
                lockClick = true;
                Vector2i localPosition = Mouse::getPosition(window);
                for (pair<string, GuiElement*> element : guiElements)
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
        else if (windowEvent.type == sf::Event::MouseButtonReleased && windowEvent.mouseButton.button == sf::Mouse::Left)
        {
            lockClick = false;
        }
        else if (windowEvent.type == Event::TextEntered && !lockInput && focus != nullptr)
        {
            if (windowEvent.text.unicode < 128)
            {
                lockInput = true;
                sf::String input = static_cast<char>(windowEvent.text.unicode);
                focus->setText(input);
            }
        }
        else if (windowEvent.type == Event::KeyReleased)
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
            organism->drawGrid();
        for (pair<string, GuiElement*> element : guiElements)
            window.draw(*element.second);
        window.display();
        if (simulation != nullptr)
            simulation->display();
    }
    return 0;
}