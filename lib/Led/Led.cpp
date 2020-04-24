#include <Arduino.h>
#include "Led.h"

Led::Led(uint8_t pinRed, uint8_t pinGreen, uint8_t pinBlue)
{
    _pinRed = pinRed;
    _pinGreen = pinGreen;
    _pinBlue = pinBlue;
}

void Led::setup()
{
    pinMode(_pinRed, OUTPUT);
    pinMode(_pinBlue, OUTPUT);
    pinMode(_pinGreen, OUTPUT);
    setColor(Color::OFF);
}

void Led::setColor(Color color)
{
    switch (color)
    {
    case Color::RED:
        setColor(HIGH, LOW, LOW);
        break;
    case Color::GREEN:
        setColor(LOW, HIGH, LOW);
        break;
    case Color::BLUE:
        setColor(LOW, LOW, HIGH);
        break;
    case Color::YELLOW:
        setColor(HIGH, HIGH, LOW);
        break;
    case Color::MAGENTA:
        setColor(HIGH, LOW, HIGH);
        break;
    case Color::CYAN:
        setColor(LOW, HIGH, HIGH);
        break;
    case Color::WHITE:
        setColor(HIGH, HIGH, HIGH);
        break;
    case Color::OFF:
    default:
        setColor(LOW, LOW, LOW);
        break;
    };
}

void Led::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
    digitalWrite(_pinRed, red);
    digitalWrite(_pinGreen, green);
    digitalWrite(_pinBlue, blue);
}
