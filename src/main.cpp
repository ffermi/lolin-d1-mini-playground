#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Led.h>

Led led(D5, D6, D7);

/* Init Function, execute at every device start */
void setup()
{
    Serial.begin(9600);
    led.setup();

    // Set WiFi to station mode and disconnect from an AP
    // (in case it was previously connected)
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");
}

void scanWiFiNetworks()
{
    Serial.println("scan start");
    // WiFi.scanNetworks will return the number of networks found
    //scanNetworks(bool async, bool show_hidden, uint8 channel, uint8* ssid)
    int n = WiFi.scanNetworks(false, false, 0, NULL);
    Serial.println("scan done");

    if (n == 0)
    {
        Serial.println("no networks found");
    }
    else
    {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i)
        {
            //Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print("CH");
            Serial.print(WiFi.channel(i));
            Serial.print(" ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");

            delay(10);
        }
    }
    Serial.println("");
}

/* Loop Function, executing for every device cycle */
void loop()
{
    //scanWiFiNetworks();

    // Wait a bit before scanning again
    Serial.println("Wait 3 minutes...");
    delay(3 * 60000);
}