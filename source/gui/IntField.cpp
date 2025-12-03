#include <cmath>

#include "IntField.h"

using namespace std;

IntField::IntField(Vector2f position, Vector2f size, int min, int max, void (*function)(const GuiElement*), int value) : InputField(position, size, function)
{
    this->min = min;
    this->max = max;
    value = std::min(max, std::max(min, value));
    this->text = to_string(value);
}

void IntField::setText(string text)
{
    text = text[0];
    if ((int)text[0] == 8)
    {
        this->text = this->text.substr(0, this->text.length() - 1);
        if (this->text.length() == 0)
            this->text = "0";
        return;
    }
    if (isdigit(text[0]))
        InputField::setText(text);
    int value = atoi(this->text.c_str());
    value = std::min(max, std::max(min, value));
    this->text = to_string(value);
}

int IntField::getValue()
{
    return stoi(this->text);
}