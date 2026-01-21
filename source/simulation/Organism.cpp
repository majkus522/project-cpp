#include <SFML/Graphics.hpp>
#include "Organism.h"
#include <cmath>
#include <iostream>

#include "../Settings.h"
#include <random>

using namespace sf;
using namespace std;

unsigned int Organism::calcSize(int a)
{
    return a * Settings::gridSize;
}

float randomFloat()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(gen);
}

void color(int x, int y, Color color, Image& image)
{
    for (int dx = 0; dx < Settings::gridSize; dx++)
    {
        for (int dy = 0; dy < Settings::gridSize; dy++)
        {
            image.setPixel(x * Settings::gridSize + dx, y * Settings::gridSize + dy, color);
        }
    }
}

Organism::Organism(Vector2i size) : size(size)
{
    cells = {};
    for (int y = 0; y < size.y; y++)
    {
        vector<int> row;
        for (int x = 0; x < size.x; x++)
        {
            row.push_back(0);
        }
        cells.push_back(row);
    }
    cells[ceil(size.y / 2)][ceil(size.x / 2)] = 1;
    newCells = cells;
}

void Organism::draw(RenderTarget& target, RenderStates states) const
{
    Image image;
    image.create(calcSize(size.x), calcSize(size.y), Color(0, 100, 0));
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            if (cells[y][x] > 0)
                color(x, y, Settings::colorSick.getColor((float)(cells[y][x] - 1) / (float)(Settings::timeSick * 2)), image);
            else if (cells[y][x] < 0)
                color(x, y, Settings::colorResistant.getColor((float)(-cells[y][x] - 1) / (float)(Settings::timeResistant * 2)), image);
            else
                color(x, y, Settings::colorNormal, image);
        }
    }
    Texture texture;
    texture.loadFromImage(image, IntRect(0, 0, calcSize(size.x), calcSize(size.y)));
    Sprite bufferSprite(texture);
    bufferSprite.setPosition(550, 10);
    target.draw(bufferSprite, states);
}

void Organism::tick()
{
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            if (cells[y][x] > 0)
            {
                newCells[y][x] += 1;
                for (int dy = -1; dy <= 1; dy++)
                {
                    for (int dx = -1; dx <= 1; dx++)
                    {
                        if (y + dy < 0 || y + dy >= size.y || x + dx < 0 || x + dx >= size.x)
                            continue;
                        if (dx != 0 || dy != 0)
                            if (cells[y + dy][x + dx] == 0)
                                if (randomFloat() < Settings::spreadChance)
                                    newCells[y + dy][x + dx] = 1;
                    }
                }
                if (cells[y][x] > Settings::timeSick)
                {
                    newCells[y][x] = -1;
                }
            }
            else if (cells[y][x] < 0)
            {
                newCells[y][x] -= 1;
                if (cells[y][x] < -Settings::timeResistant)
                {
                    newCells[y][x] = 0;
                }
            }
        }
    }
    cells = newCells;
}

void Organism::resize(Vector2i newSize)
{
    int diffX = floor((newSize.x - size.x) / 2);
    int diffY = floor((newSize.y - size.y) / 2);
    newCells = {};
    for (int y = 0; y < newSize.y; y++)
    {
        vector<int> row;
        for (int x = 0; x < newSize.x; x++)
        {
            row.push_back(0);
        }
        newCells.push_back(row);
    }
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            if (x + diffX < 0 || x + diffX >= newSize.x || y + diffY < 0 || y + diffY >= newSize.y)
                continue;
            newCells[y + diffY][x + diffX] = cells[y][x];
        }
    }
    cells = newCells;
    size = newSize;
}

void Organism::click(Vector2i position)
{
    int radius = min(size.x, size.y) / 40;
    for (int dy = -radius; dy <= radius; dy++)
    {
        int xLimit = static_cast<int>(std::sqrt(radius * radius - dy * dy));
        for (int dx = -xLimit; dx <= xLimit; dx++)
        {
            if (position.y + dy < 0 || position.y + dy >= size.y || position.x + dx < 0 || position.x + dx >= size.x)
                continue;
            cells[position.y + dy][position.x + dx] = 1;
            newCells[position.y + dy][position.x + dx] = 1;
        }
    }
}