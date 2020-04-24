#include <Arduino.h>

enum Color
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    MAGENTA,
    CYAN,
    WHITE,
    OFF
};

class Led
{
private:
    uint8_t _pinRed, _pinGreen, _pinBlue;
    uint8_t _red, _green, _blue;
    void setColor(uint8_t red, uint8_t green, uint8_t blue);

public:
    Led(uint8_t pinRed, uint8_t pinGreen, uint8_t pinBlue);
    void setup();
    void setColor(Color color);
};
