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
  else if (var == "stripeeffect")
  {
    return currentPatternName;
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

  return String();
}
// WIFI
const char *ssidAP = "ESP32-LedMatrixClock"; // IN CASE WE CANNOT CONNECT TO THE WIFI THE ESP32 WILL PRESENT ITSELF AS AN ACCESSPOINTER USING THIS NAME
const char *passwordAP = "1234abcd";         // AND YOU CAN ACCESS THAT ACCESSPOINT USING THIS SIMPLE PASSWORD
/* Function to run in ACCESSPOINT MODE */
// RunAPmode code
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
              /*
                 The website will send the parameters that the user selects
                 This part catches the paramters and stores them in preferences.
                 This can later be picked-up by the rest of the code.
                 These user parameters also will to be put in the GLOBALS.
              */
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
  // AsyncElegantOTA.begin(&server); // Start ElegantOTA
  server.begin();

  // for (;;)
  // {
  //   AsyncElegantOTA.loop();
  // }
}
