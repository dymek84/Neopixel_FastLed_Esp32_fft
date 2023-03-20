#pragma once

#include "Imports.h"

// PREFERENCES
Preferences preferences; // We will store our variables here that we don't want to loose

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

String
    whichFX,
    digitAnimation,
    digitHTMLcol,
    BGHTMLcol,
    scrolltext,
    city,
    apikey;
int
    overAllBrightness,
    digitColor,
    backgroundBrightness,
    digitBrightness,
    backgroundColor,
    scrollspeed;
/*
   Find and replace method, to inject variables into a HTML page
*/
String processor(const String &var)
{
    if (var == "effect")
    {
        return whichFX;
    }
    else if (var == "digitOnOff")
    {
        return digitAnimation;
    }
    else if (var == "digitHTMLcol")
    {
        return digitHTMLcol;
    }
    else if (var == "BGHTMLcol")
    {
        return BGHTMLcol;
    }
    else if (var == "overAllBrightness")
    {
        return String(overAllBrightness);
    }
    else if (var == "backgroundBrightness")
    {
        return String(backgroundBrightness);
    }
    else if (var == "digitBrightness")
    {
        return String(digitBrightness);
    }

    else if (var == "scrolltext")
    {
        return String(scrolltext);
    }
    else if (var == "scrollspeed")
    {
        return String(scrollspeed);
    }
    else if (var == "city")
    {
        return String(city);
    }
    else if (var == "apikey")
    {
        return String(apikey);
    }
    return String();
}

/*
   This function runs the main webpage and handles all webtrafic.
   New settings will be stored in the globals AND in memory
*/
void RunWebserver()
{
    AsyncWebServer server(80);                 // Start the webserver
    Serial.print("The IP of Men cave leds: "); // SHOW IP IN SERIAL MONITOR
    Serial.println(WiFi.localIP());

    // Serial.println(xPortGetCoreID()); // Webserver should run on second core (0)

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
                  /*
                     The website will send the parameters that the user selects
                     This part catches the paramters and stores them in preferences.
                     This can later be picked-up by the rest of the code.
                     These user parameters also will to be put in the GLOBALS.
                  */
                  if (request->hasParam("effect"))
                  {
                      inputMessage = request->getParam("effect")->value();
                      preferences.putString("effect", inputMessage);
                      // writeFile(SPIFFS, "/inputString.txt", inputMessage.c_str());
                      whichFX = inputMessage;
                  }
                  else if (request->hasParam("digitOnOff"))
                  {
                      inputMessage = request->getParam("digitOnOff")->value();
                      preferences.putString("digitOnOff", inputMessage);
                      digitAnimation = inputMessage;
                  }
                  else if (request->hasParam("inputDigitCol"))
                  {
                      inputMessage = request->getParam("inputDigitCol")->value();
                      // preferences.putString("inputDigitCol", inputMessage);
                      digitColor = strtol(inputMessage.substring(1).c_str(), NULL, 16);
                      // Serial.print("submitted color digit long: ");
                      // Serial.println(digitColor);
                      preferences.putLong("inputDigitCol", digitColor);
                      preferences.putString("digitHTMLcol", inputMessage);
                      digitHTMLcol = inputMessage;
                  }
                  else if (request->hasParam("inputBGCol"))
                  {
                      inputMessage = request->getParam("inputBGCol")->value();
                      backgroundColor = strtol(inputMessage.substring(1).c_str(), NULL, 16);
                      preferences.putLong("inputBGCol", backgroundColor);
                      preferences.putString("BGHTMLcol", inputMessage);
                      BGHTMLcol = inputMessage;
                  }

                  else if (
                      request->hasParam("overAllBrightness"))
                  {
                      inputMessage = request->getParam("overAllBrightness")->value();
                      overAllBrightness = inputMessage.toInt();
                      preferences.putUInt("oaBrightness", overAllBrightness);
                  }
                  else if (
                      request->hasParam("backgroundBrightness"))
                  {
                      inputMessage = request->getParam("backgroundBrightness")->value();
                      backgroundBrightness = inputMessage.toInt();
                      preferences.putUInt("bgBrightness", backgroundBrightness);
                  }
                  else if (
                      request->hasParam("digitBrightness"))
                  {
                      inputMessage = request->getParam("digitBrightness")->value();
                      preferences.putUInt("fgBrightness", inputMessage.toInt());
                      digitBrightness = inputMessage.toInt();
                  }

                  else if (
                      request->hasParam("scrolltext"))
                  {
                      inputMessage = request->getParam("scrolltext")->value();
                      preferences.putString("scrolltext", inputMessage);
                      scrolltext = inputMessage;
                  }
                  else if (
                      request->hasParam("scrollspeed"))
                  {
                      inputMessage = request->getParam("scrollspeed")->value();
                      preferences.putString("scrollspeed", inputMessage);
                      scrollspeed = inputMessage.toInt();
                  }
                  else if (
                      request->hasParam("restart"))
                  {
                      inputMessage = "Restarting and useing new credentials";
                      ESP.restart();
                  }
                  else if (
                      request->hasParam("apikey"))
                  {
                      inputMessage = request->getParam("apikey")->value();
                      preferences.putString("apikey", inputMessage);
                      apikey = inputMessage;
                  }
                  else if (
                      request->hasParam("city"))
                  {
                      inputMessage = request->getParam("city")->value();
                      preferences.putString("city", inputMessage);
                      city = inputMessage;
                  }
                  else if (
                      request->hasParam("ldrpin"))
                  {
                      inputMessage = request->getParam("ldrpin")->value();
                      preferences.putString("ldrpin", inputMessage);
                      // ldrpin = inputMessage.toInt();
                  }
                  else if (
                      request->hasParam("ledpin"))
                  {
                      inputMessage = request->getParam("ledpin")->value();
                      preferences.putString("ledpin", inputMessage);
                      // ledpin = inputMessage.toInt();
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

/*----------------------------------------------------------------------------------------
  Platforms: ESP32 and ESP8266
  Language: C/C++/Arduino
  File: EEPROMHandler.h
  Parent: 2022_ESPMessageBoard_Neamatrix.cpp
  ----------------------------------------------------------------------------------------
  Description:
  ESP32 EEPROM
  Simple read and write string to EEPROM
----------------------------------------------------------------------------------------*/

#include <EEPROM.h>

void eepromWriteString(int address, String data)
{
    int _size = data.length();
    int i;
    for (i = 0; i < _size; i++)
    {
        EEPROM.writeChar(address + i, data[i]);
    }
    EEPROM.writeChar(address + _size, '\0'); // Add termination null character for String Data
    EEPROM.commit();                         // save to EEPROM flash
    delay(100);
}

String eepromReadString(int address, int16_t buffer_size)
{
    char data[buffer_size];
    int len = 0;
    unsigned char k;
    k = EEPROM.readChar(address);
    while (k != '\0' && len < buffer_size)
    { // Read until null character
        k = EEPROM.readChar(address + len);
        data[len] = k;
        len++;
    }
    data[len] = '\0';
    return String(data);
}
void eepromWriteChar(int address, char data)
{
    EEPROM.writeChar(address, data);
    EEPROM.commit(); // save to EEPROM flash
    delay(100);
}

char eepromReadChar(int address)
{
    return EEPROM.readChar(address);
}

void eepromWriteInt(int address, int data)
{
    EEPROM.writeInt(address, data);
    EEPROM.commit(); // save to EEPROM flash
    delay(100);
}

int eepromReadInt(int address)
{
    return EEPROM.readInt(address);
}

void eepromWriteByte(int address, byte data)
{
    EEPROM.write(address, data);
    EEPROM.commit(); // save to EEPROM flash
    delay(100);
}

byte eepromReadByte(int address)
{
    return EEPROM.read(address);
}
