#pragma once

#include "Imports.h"

// WIFI
const char *ssidAP = "ESP32-LedMatrixClock"; // IN CASE WE CANNOT CONNECT TO THE WIFI THE ESP32 WILL PRESENT ITSELF AS AN ACCESSPOINTER USING THIS NAME
const char *passwordAP = "1234abcd";         // AND YOU CAN ACCESS THAT ACCESSPOINT USING THIS SIMPLE PASSWORD

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

String scanNetworks()
{
    // scan for nearby networks:
    String networkList = "<h3> == Available Networks == </h2>";
    byte numSsid = WiFi.scanNetworks();
    for (int thisNet = 0; thisNet < numSsid; thisNet++)
    {
        networkList += "<br/> ";
        networkList += thisNet;
        networkList += " Network: ";
        networkList += WiFi.SSID(thisNet);
    }
    return networkList;
} // scanNetworks()
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
    backgroundBrightness,
    digitBrightness,
    scrollspeed;
/*
   Find and replace method, to inject variables into a HTML page
*/
String processor(const String &var)
{
    // String "#";
    if (var == "wifilist")
    {
        return scanNetworks();
    }
    else if (var == "effect")
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

    else if (var == "ldrpin")
    {
        // return String(ldrpin);
    }
    else if (var == "ledpin")
    {
        // return String(ledpin);
    }
    else if (var == "animatechange")
    {
        // return String(animatechange);
    }
    return String();
}

/* Function to run in ACCESSPOINT MODE */
// RunAPmode code
void RunAPmode(void *parameter)
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
            timeMatrix = showText(scrolltextip, CRGB::Red, textScroller);
            bgMatrix = getBackgroundMap(timeMatrix);
            bgMatrix = oneColorBackground(bgMatrix, CRGB::Black);
            textScroller++;
            counter++;
        }
        mergeMapsToLeds(bgMatrix, timeMatrix, 128, 128, false, false); // Merge both matrices. before we display.
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
            timeMatrix = showText(scrolltextip, CRGB::Red, textScroller);
            bgMatrix = getBackgroundMap(timeMatrix);
            bgMatrix = oneColorBackground(bgMatrix, CRGB::Black);
            textScroller++;
            counter++;
        }
        mergeMapsToLeds(bgMatrix, timeMatrix, 128, 128, false, false); // Merge both matrices. before we display.
        FastLED.show();
    }
}

/*
   This function runs the main webpage and handles all webtrafic.
   New settings will be stored in the globals AND in memory
*/
void RunWebserver(void *parameter)
{
    AsyncWebServer server(80);            // Start the webserver
    Serial.print("The IP of ledclock: "); // SHOW IP IN SERIAL MONITOR
    Serial.println(WiFi.localIP());
    Serial.print("The wifi server runs on core: ");
    Serial.println(xPortGetCoreID()); // Webserver should run on second core (0)

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
                      request->hasParam("LDR"))
                  {
                      int MeasuredValue = 0;
                      if (useLDR)
                      {
                          MeasuredValue = analogRead(sensorPin);
                          Serial.println(MeasuredValue);
                      }
                      else
                      {
                          MeasuredValue = 0;
                      }
                      inputMessage = MeasuredValue;
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
                  else if (
                      request->hasParam("animatechange"))
                  {
                      inputMessage = request->getParam("animatechange")->value();
                      preferences.putString("animatechange", inputMessage);
                      animatechange = inputMessage;
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
    AsyncElegantOTA.begin(&server); // Start ElegantOTA
    server.begin();

    for (;;)
    {
        AsyncElegantOTA.loop();
    }
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

        xTaskCreatePinnedToCore(
            RunWebserver,   // Function to implement the task
            "RunWebserver", // Name of the task
            10000,          // Stack size in words
            NULL,           // Task input parameter
            0,              // Priority of the task
            &Wifimode,      // Task handle.
            0);             // Core where the task should run

        FastLED.delay(1000); // to allow to start the 2nd processor.
        connectedToNetwork = true;
    }
    else
    {
        Serial.println("No WIFI, let's offer an accesspoint");

        // We can start as ACCESSPOINT
        xTaskCreatePinnedToCore(
            RunAPmode,
            "RunAPmode",
            10000,
            NULL,
            0,
            &APmode,
            0);

        FastLED.delay(1000); // to allow to start the 2nd processor.
        connectedToNetwork = false;
    }
    while (!connectedToNetwork)
    { // When we are not connected to a router (wifi point) we should not proceed. But only show the accesspoint website
        EVERY_N_SECONDS(30)
        {
            // Serial.println("ESP Matrix Clock is in AccessPoint mode. Please enter your SSID and Key in the Accesspoint website (connect to the AP-wifi first)");
            displayIPAP();
        }
    }
    configTzTime(defaultTimezone, ntpServer); // sets TZ and starts NTP sync
    // configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    if (updateLocalTime())
    {
        Serial.println("We have network time");

        Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
        displayIP(); // Display the last digits of the IP on the matrix.
    }
    else
    {

        Serial.println("No Network time was obtained, therefore we will reboot to try again");
        ESP.restart();
    }
}
String handleAP(uint8_t *data, size_t len)
{
    String returnstring;

    data[len] = '\0';
    String json = (char *)data;

    DynamicJsonDocument doc(JSON_OBJECT_SIZE(3) + 130);
    DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

    if (error)
    { // Test if parsing succeeds.
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return "deserializeJson error";
    }

    const char *oldpassword = doc["oldpassword"];
    const char *newpassword = doc["newpassword"];
    const char *renewpassword = doc["renewpassword"];

    if (String(oldpassword) == String(password) && String(newpassword) == String(renewpassword))
    {
        returnstring = "password:" + String(password) + " newpassword:" + String(newpassword) + " renewpassword:" + String(renewpassword);
        Serial.print("password handle: ");
        Serial.println(json);
        eepromWriteChar(BUF_SIZE, '\0');     // wall so message doesnt display password at max buffer pos
        eepromWriteChar(PASS_EXIST, P_CHAR); // user password now exists
        eepromWriteString(PASS_ADDR, String(newpassword));
        Serial.println("new password saved");
        Serial.println(eepromReadChar(PASS_ADDR));
        WiFi.softAPdisconnect();
        delay(8000);
        ESP.restart();
    }
    else
    {
        returnstring = "error, passwords don't match";
        Serial.print("password handle error: ");
        Serial.println(json);
        Serial.println("\nerror, passwords don't match\n");
        delay(1000);
    }

    return returnstring;
}

String handleMessageUpdate(uint8_t *data, size_t len)
{
    data[len] = '\0';
    String json = (char *)data;

    DynamicJsonDocument doc(JSON_OBJECT_SIZE(2) + 350);
    DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

    if (error)
    { // Test if parsing succeeds.
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return "deserializeJson error";
    }

    BRIGHT = int(doc["brightness"]);
    strcpy(newMessage, doc["message"]);

    Serial.print("message and brightness handle: ");
    Serial.println(json);

    newMessageAvailable = true;

    // return json;
    return "{\"status\" : \"ok\", \"data\" : \"" + json + "\"}";
}

void updateDefaultAPPassword()
{
    Serial.println("updateDefaultAPPassword");
    if (eepromReadChar(PASS_EXIST) == P_CHAR)
    {
        delay(200);
        Serial.print("user pwd found: \"");
    }
    else
    {
        delay(200);
        Serial.println("\nuser pwd is not found\nrestoring default pwd to ");

        eepromWriteChar(BUF_SIZE, '\0');          // wall so message doesnt display password at max buffer pos
        eepromWriteChar(PASS_EXIST, P_CHAR);      // user password now exists
        eepromWriteString(PASS_ADDR, "password"); // default password is "password"
    }

    String eeString = eepromReadString(PASS_ADDR, PASS_BSIZE);
    eeString.toCharArray(password, eeString.length() + 1);

    Serial.print(eeString);
    Serial.print("\" from EEPROM.\n\"");
    Serial.print(password);
    Serial.println("\" is used as the WIFI pwd");
    delay(1000);
}

void handleServer()
{

    //  WIFI 2
    Serial.print("\nWIFI >> Connecting to ");
    Serial.println(ssid);

    updateDefaultAPPassword(); // get Wifi password from EEPROM

    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(ip, ip, subnet);
    WiFi.softAP(ssid, password);
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
    server.on(
        "/message", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
        [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        {
            String myResponse = handleMessageUpdate(data, len);
            request->send(200, "text/plain", myResponse);
        });

    server.onNotFound([](AsyncWebServerRequest *request)
                      { request->send(SPIFFS, "/notfound.html", "text/html"); });

    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/favicon.png", "image/png"); });

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    AsyncElegantOTA.begin(&server); //* OTA - Start ElegantOTA
    server.begin();
    Serial.println("SERVER STARTED");
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
