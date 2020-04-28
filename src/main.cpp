#include <Arduino.h>
#include <Led.h>

Led led(D5, D6, D7); 

void setup()
{
    Serial.begin(9600);
    led.setup();
}

void loop()
{
    led.setColor(Color::GREEN);
    delay(500);
    led.setColor(Color::WHITE);
    delay(500);
    led.setColor(Color::RED);
    delay(500);
    led.setColor(Color::OFF);
    delay(500);
}