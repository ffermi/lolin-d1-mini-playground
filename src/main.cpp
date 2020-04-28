#include <Arduino.h>
#include <Led.h>
#include <OneButton.h>

Led led(D5, D6, D7); 
OneButton button(D8, false);

void onClick(){
    Serial.println("Button click.");

    led.setColor(Color::GREEN); 
    delay(100);
    led.setColor(Color::OFF);
}

void onDoubleClick(){
    Serial.println("Button double click.");

    led.setColor(Color::BLUE); 
    delay(100);
    led.setColor(Color::OFF);
    delay(100);
    led.setColor(Color::BLUE); 
    delay(100);
    led.setColor(Color::OFF);
}

void onLongClickStart(){
    Serial.println("Button long click started.");
    led.setColor(Color::RED);  
}

void onLongClickStop(){
    Serial.println("Button long click ended.");
    led.setColor(Color::OFF);  
}

/* Init Function, execute at every device start */
void setup()
{
    Serial.begin(9600);

    led.setup();

    pinMode(D8, INPUT);
    button.attachClick(onClick);
    button.attachDoubleClick(onDoubleClick);
    button.attachLongPressStart(onLongClickStart);
    button.attachLongPressStop(onLongClickStop);
}

/* Loop Function, executing for every device cycle */
void loop()
{
    // keep watching the push button:
    button.tick();
    
    // You can implement other code in here or just wait a while 
    delay(10);
}