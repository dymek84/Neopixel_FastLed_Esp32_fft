#pragma once

#include "Imports.h"

String elementValue1 = "effectus";
String elementValue2 = "0";
String message = "";

void notifyClients()
{

    const uint8_t size = JSON_OBJECT_SIZE(1);
    StaticJsonDocument<size> json;
    json["currentEffect"] = String(elementValue1);
    json["sliderValue2"] = String(elementValue2);

    char buffer[99];
    size_t len = serializeJson(json, buffer);
    ws.textAll(buffer, len);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
    {

        const uint8_t size = JSON_OBJECT_SIZE(1);
        StaticJsonDocument<size> json;
        DeserializationError err = deserializeJson(json, data);
        if (err)
        {
            Serial.print(F("deserializeJson() failed with code "));
            Serial.println(err.c_str());
            return;
        }

        const char *action = json["action"];
        if (strcmp(action, "toggle") == 0)
        {

            notifyClients();
        }
    }
}
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    switch (type)
    {
    case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
    case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
    case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
        break;
    }
}
void initWebSocket()
{
    ws.onEvent(onEvent);
    server.addHandler(&ws);
}
const char INDEXAP_HTML[] PROGMEM = R"rawliteral(

<!DOCTYPE HTML>
<html>
<head>
    <meta content="text/html; charset=ISO-8859-1" http-equiv="content-type">
    <meta name="viewport" content="width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0">
    <title> ESP32 Led Matrix Clock, update your, WIFI SETTINGS</title>
    <style>
        body {
            background-color: #808080;
            font-family: Arial, Helvetica, Sans-Serif;
            Color: #000000;
            text-align: center;
        }
    </style>
</head>
<body>
    <h3> Enter your WiFi credentials</ h3>
        <form action="/get" target="hidden-form">
            <p><label> SSID : &nbsp;</label>
                <input maxlength="30" name="SSIDname"><br>
                <input type="submit" value="Save">
        </form>
        <form action="/get" target="hidden-form">
            <label>Key: </label><input maxlength="30" name="SSIDpwd"><br>
            <input type="submit" value="Save">
            </p>
        </form>
        <form action="/get" target="hidden-form">
            Press this button to reboot with the new Password and SSID name<br />
            <input type="submit" value="Reboot">
            <br />
        </form>
        <p></p>
        <iframe style="display:none" name="hidden-form"></iframe>
</body>
</html>
  )rawliteral";
boolean connectToNetwork(String s, String p)
{
    const char *ssid = s.c_str();
    const char *password = p.c_str();

    Serial.print("ACCESSING WIFI: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    int timeout = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(2000);
        Serial.println("Connecting to WiFi..");
        if (timeout == 5)
        {
            return false;
            break;
        }
        Serial.println(".");
        timeout++;
    }
    Serial.println(WiFi.localIP());
    return true;
} // network()
/*
   Sometimes a page just doesn't exists.. we need to tell them
*/
void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
} // runAPmode()

/*
   Find and replace method, to inject variables into a HTML page
*/
String processor(const String &var)
{
    if (var == "patternLED")
    {
        return patternLED;
    }
    else if (var == "paletteLED")
    {
        return paletteLED;
    }
    else if (var == "patternMatrix")
    {
        return patternMatrix;
    }
    else if (var == "paletteMatrix")
    {
        return paletteMatrix;
    }
    else if (var == "overAllBrightness")
    {
        return String(overAllBrightness);
    }
    else if (var == "scrolltext")
    {
        return String(scrolltext);
    }
    else if (var == "SSID")
    {
        return String(SSID);
    }
    else if (var == "password")
    {
        return String(password);
    }
    return String();
}
void RunAPmode()
{
    WiFi.disconnect(true); // End All connections.
    AsyncWebServer server(80);
    WiFi.softAP(ssidAP, passwordAP);                               // Start ACCESSPOINT MODE with basic credentials
    IPAddress IP = WiFi.softAPIP();                                // GET THE ACCESSPOINT IP
    Serial.println("The IP of the settings page is: 192.168.4.1"); // SHOW IP IN SERIAL MONITOR
    // Serial.println(WiFi.localIP());
    preferences.begin("wificreds", false);                        // Make sure we have something to store our preferences in
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { // The Home page so to say.
        request->send_P(200, "text/html", INDEXAP_HTML, processor);
    });

    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) { // WHEN SOMEONE SUBMITS SOMETHING.... Like the credentials :)
        String inputMessage;
        const char *PARAM_WIFI = "SSIDname";
        const char *PARAM_PWD = "SSIDpwd";
        preferences.begin("wificreds", false);

        if (request->hasParam(PARAM_WIFI))
        {
            inputMessage = request->getParam(PARAM_WIFI)->value();
            preferences.putString("ssid", inputMessage);
        }
        else if (request->hasParam(PARAM_PWD))
        {
            inputMessage = request->getParam(PARAM_PWD)->value();
            preferences.putString("password", inputMessage);
        }
        else
        {
            inputMessage = "Restarting and using new credentials";
            ESP.restart();
        }
        Serial.println(inputMessage); // This prints the submitted variable on the serial monitor.. as a check
        request->send(200, "text/text", inputMessage);
    });
    server.onNotFound(notFound);
    server.begin();
    Serial.print("AP mode runs on core: ");
    Serial.println(xPortGetCoreID());

    for (;;)
    {
        preferences.begin("wificreds", false);
        delay(5000);
        Serial.print(".");
        //  Serial.println(preferences.getString("ssid"));
        //  Serial.println(preferences.getString("password"));
        preferences.end();
    }
}

void displayIP()
{
    String ip = WiFi.localIP().toString();
    int textScroller = -34;
    int counter = 0;
    String scrolltextip = "ip: " + ip;
    int textlentgh = scrolltextip.length();

    while (counter < (textlentgh * 10 * 1))
    {
        EVERY_N_MILLISECONDS(50)
        {

            if (textScroller >= textlentgh * 7)
            {
                textScroller = -34;
            }

            textScroller++;
            counter++;
        }

        FastLED.show();
    }
}

void displayIPAP()
{
    String ip = WiFi.localIP().toString();
    int textScroller = -34;
    int counter = 0;
    String scrolltextip = "accesspoint ip: 192.168.4.1";
    int textlentgh = scrolltextip.length();

    while (counter < (textlentgh * 8 * 2))
    {
        EVERY_N_MILLISECONDS(80)
        {

            if (textScroller >= textlentgh * 7)
            {
                textScroller = -34;
            }

            textScroller++;
            counter++;
        }

        FastLED.show();
    }
}

/*
   This function runs the main webpage and handles all webtrafic.
   New settings will be stored in the globals AND in memory
*/
void RunWebserver()
{
    // AsyncWebServer server(80);            // Start the webserver
    Serial.print("The IP of ledclock: "); // SHOW IP IN SERIAL MONITOR
    Serial.println(WiFi.localIP());
    // Serial.print("The wifi server runs on core: ");
    // Serial.println(xPortGetCoreID()); // Webserver should run on second core (0)
    //  SPIFFS
    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
    else
    {
        // listDir(SPIFFS, "/", 2);
    }
    // server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", String(), false, processor); });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/style.css", "text/css"); });

    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/script.js", "text/css"); });
    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  preferences.end(); // In case preferences was still 'open' but in a different 'domain'
                  String inputMessage;
                  preferences.begin("matrixsettings", false); // Open the matrixsettings preferences 'domain'
                  Serial.print("New variable received: ");
                  int i;
                  int params = request->params();
                  for (i = 0; i < params; i++)
                  {
                      AsyncWebParameter *p = request->getParam(i);
                      if (p->isFile())
                      {
                          Serial.printf("_FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
                      }
                      else if (p->isPost())
                      {
                          Serial.printf("_POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
                      }
                      else
                      {
                          Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
                      }
                  }

                  if (request->hasParam("patternLED"))
                  {
                      inputMessage = request->getParam("patternLED")->value();
                      // preferences.putString("patternLED", inputMessage);
                      //  writeFile(SPIFFS, "/inputString.txt", inputMessage.c_str());
                      Serial.println("received patternLED");
                      Serial.println(inputMessage);
                      nextPattern();
                      request->send(200, "text/text", "success");
                  }
                  else if (request->hasParam("overAllBrightness"))
                  {
                      inputMessage = request->getParam("overAllBrightness")->value();
                      overAllBrightness = inputMessage.toInt();
                      preferences.putUInt("oaBrightness", overAllBrightness);
                  }
                  else if (request->hasParam("scrolltext"))
                  {
                      inputMessage = request->getParam("scrolltext")->value();
                      preferences.putString("scrolltext", inputMessage);
                      scrolltext = inputMessage;
                  }
                  else if (request->hasParam("scrollspeed"))
                  {
                      inputMessage = request->getParam("scrollspeed")->value();
                      preferences.putString("scrollspeed", inputMessage);
                      scrollspeed = inputMessage.toInt();
                  }
                  else
                  {
                      inputMessage = "No message sent";
                  }
                  // request->send(SPIFFS, "/index.html", "text/html");
                  request->send(200, "text/text", inputMessage);
                  preferences.end(); // don't leave the door open :) always close when you leave.
              });
    notifyClients();
    server.onNotFound(notFound);
    server.begin();
}
void listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if (!root)
    {
        Serial.println("- failed to open directory");
        return;
    }
    if (!root.isDirectory())
    {
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if (levels)
            {
                listDir(fs, file.path(), levels - 1);
            }
        }
        else
        {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}
void webSetup()
{
    /*
       Let's setup a wifi connection
       False: no wifi connection to router. If that is the case, we will setup an AP
       True: yeah... we have a network connection. An now we can proceed!!
       We will run our webserver stuff on a different core, so all the led stuff can stay on the other core..
    */
    boolean connectedToNetwork = false; // We want to know if we have a network before proceeding

    preferences.begin("wificreds", false); // The WIFI credentials are stored here
    delay(1000);

    preferences.getString("ssid");

    //  SPIFFS
    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
    else
    {
        listDir(SPIFFS, "/", 2);
    }

    // Connect to network
    // This can be false... no WIFI access and we need a way to set this via ACCESSPOINT more.
    if (connectToNetwork(preferences.getString("ssid"), preferences.getString("password")))
    {

        RunWebserver(); // Function to implement the task

        FastLED.delay(1000); // to allow to start the 2nd processor.
        connectedToNetwork = true;
    }
}
