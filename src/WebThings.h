#pragma once

#include "Imports.h"
uint8_t patternNumber = 0;

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
void onRootRequest(AsyncWebServerRequest *request)
{
    request->send(SPIFFS, "/index.html", "text/html", false, processor);
}
void notifyClients(String message = "Default", String type = "Default")
{
    ws.printfAll("{\"%s\":\"%s\"}", message, type);
}

/*
   Sometimes a page just doesn't exists.. we need to tell them
*/
void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
} // runAPmode()

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

void RunAPmode()
{
    WiFi.disconnect(true); // End All connections.
    WiFi.mode(WIFI_AP);
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

// ----------------------------------------------------------------------------
// Web server initialization
// ----------------------------------------------------------------------------

void initWebServer()
{
    server.on("/", onRootRequest);
    server.serveStatic("/", SPIFFS, "/");

    server.on("/logo", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/logo.png", "image/png"); });
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

    server.onNotFound(notFound);
    server.begin();
    Serial.print("Web server runs on core: ");
    Serial.println(xPortGetCoreID());
}

// ----------------------------------------------------------------------------
// WebSocket initialization
// ----------------------------------------------------------------------------

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
    {

        const uint8_t size = JSON_OBJECT_SIZE(6);
        StaticJsonDocument<size> json;
        DeserializationError err = deserializeJson(json, data);
        if (err)
        {
            Serial.print(F("deserializeJson() failed with code "));
            Serial.println(err.c_str());
            return;
        }

        const char *action = json["action"];
        if (strcmp(action, "nextPattern") == 0)
        {
            nextPattern();
            notifyClients("patternName", String(patternsStripe[CurrentStripePatternNumber].name));
            preferences.putString("patternNumber", String(patternNumber));
        }
        if (strcmp(action, "prevPattern") == 0)
        {
            prevPattern();
            notifyClients("patternName", String(patternsStripe[CurrentStripePatternNumber].name));
            preferences.putString("patternNumber", String(patternNumber));
        }
        if (strcmp(action, "stripPatternSpeedUp") == 0)
        {
            patternInterval <= 1 ? patternInterval == 1 : patternInterval -= 10;
            notifyClients("stripePatternSpeed", String(256 - patternInterval));
            preferences.putString("patternInterval", String(patternInterval));
        }
        if (strcmp(action, "stripPatternSpeedDown") == 0)
        {
            patternInterval >= 256 ? patternInterval == 256 : patternInterval += 10;
            notifyClients("stripePatternSpeed", String(256 - patternInterval));
            preferences.putString("patternInterval", String(patternInterval));
        }
        if (strcmp(action, "toggle4") == 0)
        {

            notifyClients();
        }

        if (strcmp(action, "toggle5") == 0)
        {

            notifyClients();
        }

        if (strcmp(action, "toggle6") == 0)
        {

            notifyClients();
        }
        if (strcmp(action, "rank8") == 0)
        {
            Serial.print(F("rank8 action"));

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
    // notifyClients();
}

void initWebSocket()
{
    ws.onEvent(onEvent);
    server.addHandler(&ws);
    Serial.println("WebSocket server started.");
}

// ----------------------------------------------------------------------------
// SPIFFS initialization
// ----------------------------------------------------------------------------
void setupWebServer()
{

    //  initSPIFFS();
    // initWiFi();
    initWebSocket();
    initWebServer();
}
