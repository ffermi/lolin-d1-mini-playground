#include <Arduino.h>
#include <Led.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID ""
#define STAPSK ""
#endif

const char *ssid = STASSID;
const char *password = STAPSK;

ESP8266WebServer server(80);

void handleRoot()
{
    server.send(200, "text/plain", "hello from esp8266!");
}

void handleNotFound()
{
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++)
    {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

Led led(D5, D6, D7);

/* Init Function, execute at every device start */
void setup()
{
    Serial.begin(9600);
    led.setup();

    // Set WiFi to station mode and disconnect from an AP
    // (in case it was previously connected)
    // WiFi.mode(WIFI_STA);
    // WiFi.disconnect();
    // delay(100);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("esp8266"))
    {
        Serial.println("MDNS responder started");
    }

    server.on("/", handleRoot);

    server.on("/inline", []() {
        server.send(200, "text/plain", "this works as well");
    });


    server.on("/config", []() {
        server.send(200, "text/html", "<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\" /> <title>{v}</title> <style> .c { text-align: center; } div, input { padding: 5px; font-size: 1em; } input { width: 95%; } body { text-align: center; font-family: verdana; } button { border: 0; border-radius: 0.3rem; background-color: #1fa3ec; color: #fff; line-height: 2.4rem; font-size: 1.2rem; width: 100%; } .q { float: right; width: 64px; text-align: right; } .l { background: url(\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAALVBMVEX///8EBwfBwsLw8PAzNjaCg4NTVVUjJiZDRUUUFxdiZGSho6OSk5Pg4eFydHTCjaf3AAAAZElEQVQ4je2NSw7AIAhEBamKn97/uMXEGBvozkWb9C2Zx4xzWykBhFAeYp9gkLyZE0zIMno9n4g19hmdY39scwqVkOXaxph0ZCXQcqxSpgQpONa59wkRDOL93eAXvimwlbPbwwVAegLS1HGfZAAAAABJRU5ErkJggg==\") no-repeat left center; background-size: 1em; } </style> <script>function c(l) { document.getElementById('s').value = l.innerText || l.textContent; document.getElementById('p').focus(); }</script> </head> <body> <div style='text-align:left;display:inline-block;min-width:260px;'> <form action=\"/wifi\" method=\"get\"><button>Configure WiFi</button></form><br /> <form action=\"/0wifi\" method=\"get\"><button>Configure WiFi (No Scan)</button></form><br /> <form action=\"/i\" method=\"get\"><button>Info</button></form><br /> <form action=\"/r\" method=\"post\"><button>Reset</button></form> <div><a href='#p' onclick='c(this)'>{v}</a>&nbsp;<span class='q {i}'>{r}%</span></div> <form method='get' action='wifisave'><input id='s' name='s' length=32 placeholder='SSID'><br /><input id='p' name='p' length=64 type='password' placeholder='password'><br /> <br /><input id='{i}' name='{n}' maxlength={l} placeholder='{p}' value='{v}' {c}> <br /><button type='submit'>save</button></form> <br /> <div class=\"c\"><a href=\"/wifi\">Scan </a> </div> <div>Credentials Saved<br />Trying to connect ESP to network.<br />If it fails reconnect to AP to try again</div> </div> </body> </html>");
    });

    server.on("/gif", []() {
        static const uint8_t gif[] PROGMEM = {
            0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x10, 0x00, 0x10, 0x00, 0x80, 0x01,
            0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00, 0x00,
            0x10, 0x00, 0x10, 0x00, 0x00, 0x02, 0x19, 0x8c, 0x8f, 0xa9, 0xcb, 0x9d,
            0x00, 0x5f, 0x74, 0xb4, 0x56, 0xb0, 0xb0, 0xd2, 0xf2, 0x35, 0x1e, 0x4c,
            0x0c, 0x24, 0x5a, 0xe6, 0x89, 0xa6, 0x4d, 0x01, 0x00, 0x3b};
        char gif_colored[sizeof(gif)];
        memcpy_P(gif_colored, gif, sizeof(gif));
        // Set the background to a random set of colors
        gif_colored[16] = millis() % 256;
        gif_colored[17] = millis() % 256;
        gif_colored[18] = millis() % 256;
        server.send(200, "image/gif", gif_colored, sizeof(gif_colored));
    });

    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("HTTP server started");
}

void loop(void)
{
    server.handleClient();
    MDNS.update();
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