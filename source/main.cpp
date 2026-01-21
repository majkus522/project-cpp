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
#include <thread>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

using namespace sf;
using namespace std;

map<string, GuiElement*> guiElements;
bool isRunning = true;
Organism *organism;
Clock timer;
InputField *focus = nullptr;
int x;
int y;
Rect<float> simRect;

void initSettings()
{
    Settings::timeSick = ((IntField*)guiElements["fieldTimeSick"])->getValue();
    Settings::timeResistant = ((IntField*)guiElements["fieldTimeRes"])->getValue();
    Settings::spreadChance = ((IntField*)guiElements["fieldPercent"])->getValue() / 100.0f;
    Settings::delay = seconds(((IntField*)guiElements["fieldTime"])->getValue() / 1000.0f);
    x = ((IntField*)guiElements["fieldSizeX"])->getValue();
    y = ((IntField*)guiElements["fieldSizeY"])->getValue();

    VideoMode size = VideoMode::getDesktopMode();
    unsigned int pixels = min(size.width - 550, size.height - 50);
    unsigned int cells = max(x, y);
    Settings::gridSize = pixels / cells;

    if (organism != nullptr)
        organism->resize({x, y});
    simRect = Rect<float>(550, 10, x * Settings::gridSize, y * Settings::gridSize);
}

void startSimulation(const GuiElement * element)
{
    initSettings();
    isRunning = true;
    timer.restart();
}

void stopSimulation(const GuiElement * element)
{
    isRunning = false;
}

void setFocus(const GuiElement * element)
{
    focus = (InputField*)element;
    focus->setFocus(true);
}

void tick()
{
    organism->tick();
    timer.restart();
}

int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "Problem Liszaja", Style::Titlebar | Style::Close);
    timer.restart();

    guiElements.insert({"buttonStart", new Button({50, 50}, {150, 50}, "Start", startSimulation)});
    guiElements.insert({"buttonStop", new Button({200, 50}, {150, 50}, "Stop", stopSimulation)});

    guiElements.insert({ "textX", new TextElement({50, 150}, {50, 50}, "X:") });
    guiElements.insert({"fieldSizeX", new IntField({100, 150}, {100, 50}, 0, 1000, setFocus, 300)});
    guiElements.insert({ "textY", new TextElement({300, 150}, {50, 50}, "Y:") });
    guiElements.insert({"fieldSizeY", new IntField({350, 150}, {100, 50}, 0, 1000, setFocus, 300)});

    guiElements.insert({ "textTimeSick", new TextElement({50, 250}, {150, 50}, "Time sick:") });
    guiElements.insert({ "fieldTimeSick", new IntField({300, 250}, {100, 50}, 0, 100, setFocus, 6) });
    guiElements.insert({ "textTimeRes", new TextElement({50, 300}, {200, 50}, "Time resistant:") });
    guiElements.insert({ "fieldTimeRes", new IntField({300, 300}, {100, 50}, 0, 100, setFocus, 2) });
    guiElements.insert({ "textPercent", new TextElement({50, 350}, {200, 50}, "Spread percent:") });
    guiElements.insert({ "fieldPercent", new IntField({300, 350}, {100, 50}, 0, 100, setFocus, 50) });
    guiElements.insert({ "textTime", new TextElement({50, 400}, {200, 50}, "Delay [ms]:") });
    guiElements.insert({ "fieldTime", new IntField({300, 400}, {150, 50}, 10, 10000, setFocus, 100) });

    bool lockClick = false;
    bool lockInput = false;

    initSettings();
    organism = new Organism({x, y});

    Event simulationEvent;
    Event windowEvent;

    while (window.isOpen())
    {
        window.pollEvent(windowEvent);
        if (windowEvent.type == Event::Closed)
        {
            window.close();
        }
        else if (windowEvent.type == Event::MouseButtonPressed)
        {
            if (windowEvent.mouseButton.button == Mouse::Left && !lockClick)
            {
                if (focus != nullptr)
                    focus->setFocus(false);
                focus = nullptr;
                initSettings();
                lockClick = true;
                Vector2f localPosition = (Vector2f)Mouse::getPosition(window);
                for (pair<string, GuiElement*> element : guiElements)
                {
                    if (dynamic_cast<Clickable*>(element.second))
                    {
                        if (dynamic_cast<Button*>(element.second))
                            ((Button*)element.second)->click(localPosition);
                        else if (dynamic_cast<InputField*>(element.second))
                            ((InputField*)element.second)->click(localPosition);
                    }
                }
                if (simRect.contains(localPosition))
                {
                    localPosition -= Vector2f(550, 10);
                    organism->click({(int)(localPosition.x / Settings::gridSize), (int)(localPosition.y / Settings::gridSize)});
                }
            }
        }
        else if (windowEvent.type == Event::MouseButtonReleased && windowEvent.mouseButton.button == Mouse::Left)
        {
            lockClick = false;
        }
        else if (windowEvent.type == Event::TextEntered && !lockInput && focus != nullptr)
        {
            if (windowEvent.text.unicode < 128)
            {
                lockInput = true;
                sf::String input = static_cast<char>(windowEvent.text.unicode);
                if (focus->setText(input))
                {
                    focus->setFocus(false);
                    focus = nullptr;
                    initSettings();
                }
            }
        }
        else if (windowEvent.type == Event::KeyReleased)
        {
            lockInput = false;
        }

        if(timer.getElapsedTime() >= Settings::delay && isRunning)
        {
            tick();
        }

        window.clear();
        window.draw(*organism);
        for (pair<string, GuiElement*> element : guiElements)
            window.draw(*element.second);
        window.display();
    }
    return 0;
}