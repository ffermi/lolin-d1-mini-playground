#include <Arduino.h>
#include <Led.h>

Led led(D5, D6, D7); 

/* Init Function, execute at every device start */
void setup()
{
    Serial.begin(9600);
    led.setup();
}

/* Loop Function, executing for every device cycle */
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