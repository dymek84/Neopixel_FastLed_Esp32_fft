
// #pragma once

// #include "imports.h"

// String processor(const String &var)
// {
//     if (var == "welcomeMessage") ///
//     {
//         return welcomeMessage;
//     }
//     else if (var == "mBright") ///
//     {
//         return String(matrixBrightness);
//     }
//     else if (var == "sBright") ///
//     {
//         return String(stripBrightness);
//     }
//     else if (var == "patternStrName") //
//     {
//         return String(patternsStripe[CurrentStripePatternNumber].name);
//     }
//     else if (var == "patternMatName") //
//     {
//         return String(patternsMatrix[CurrentMatrixPatternNumber].name);
//     }
//     else if (var == "paletteStripe") //
//     {
//         return String(paletteList[currentPaletteStripeIndex].Name);
//     }
//     else if (var == "paletteMatrix") //
//     {
//         return String(paletteList[currentPaletteMatrixIndex].Name);
//     }
//     else if (var == "micSens")
//     {
//         return String(micSensytivity);
//     }
//     else if (var == "stripeSpeed")
//     {
//         return String(stripeSpeed);
//     }
//     else if (var == "matrixSpeed")
//     {
//         return String(matrixSpeed);
//     }
//     else if (var == "currentPatMat")
//     {
//         return String(CurrentMatrixPatternNumber);
//     }
//     else if (var == "currentPatStr")
//     {
//         return String(CurrentStripePatternNumber);
//     }
//     else if (var == "strPatMax")
//     {
//         return String(StripePatternsAmount);
//     }
//     else if (var == "matPatMax")
//     {
//         return String(MatrixPatternsAmount);
//     }
//     else if (var == "isAutoPalStripe")
//     {
//         return autoPalStr == 0 ? "unchecked" : "checked";
//     }
//     else if (var == "isAutoPalMatrix")
//     {
//         return autoPalMat == 0 ? "unchecked" : "checked";
//     }
//     else if (var == "paletteTime")
//     {
//         return String(paletteTime);
//     }
//     else if (var == "clockStatus")
//     {
//         return clockOnOff ? "The clock is on" : "The clock is off";
//     }
//     else if (var == "clockActualColor")
//     {
//         //  return String(clockColor.r + "" + clockColor.g + "" + clockColor.b);
//     }

//     return String();
// }
// String handleAutopaletteStripeUpdate(uint8_t *data, size_t len)
// {
//     data[len] = '\0';
//     String json = (char *)data;

//     DynamicJsonDocument doc(JSON_OBJECT_SIZE(2) + 350);
//     DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

//     if (error)
//     { // Test if parsing succeeds.
//         Serial.print(F("deserializeJson() failed: "));
//         Serial.println(error.f_str());
//         return "deserializeJson error";
//     }

//     preferences.begin("settings");
//     autoPalStr = int(doc["autoPalStripe"]); // 1
//     preferences.putInt("autoPalStripe", autoPalStr);
//     preferences.end();
//     Serial.print("autoPalStr: ");
//     Serial.print(autoPalStr);
//     Serial.print(" - autoPalStripe handle: ");
//     Serial.println(json);
//     // return json;
//     return "{\"status\" : \"ok\", \"data\" : \"" + String(autoPalStr) + "\"}";
// }
// String handleAutopaletteMatrixUpdate(uint8_t *data, size_t len)
// {
//     data[len] = '\0';
//     String json = (char *)data;

//     DynamicJsonDocument doc(JSON_OBJECT_SIZE(2) + 350);
//     DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

//     if (error)
//     { // Test if parsing succeeds.
//         Serial.print(F("deserializeJson() failed: "));
//         Serial.println(error.f_str());
//         return "deserializeJson error";
//     }

//     preferences.begin("settings");
//     autoPalMat = int(doc["autoPalMatrix"]); // 1
//     preferences.putInt("autoPalMatrix", autoPalMat);
//     preferences.end();
//     Serial.print("autoPalMatrix handle: ");
//     Serial.println(json);
//     // return json;
//     return "{\"status\" : \"ok\", \"data\" : \"" + String(autoPalMat) + "\"}";
// }
// String handleMicNoise(uint8_t *data, size_t len)
// {
//     data[len] = '\0';
//     String json = (char *)data;
//     DynamicJsonDocument doc(JSON_OBJECT_SIZE(2) + 350);
//     DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

//     if (error)
//     { // Test if parsing succeeds.
//         Serial.print(F("deserializeJson() failed: "));
//         Serial.println(error.f_str());
//         return "deserializeJson error";
//     }
//     micSquelch = int(doc["micNoise"]);
//     preferences.begin("settings");
//     preferences.putInt("micNoise", micSquelch);
//     preferences.end();
//     Serial.print("micNoise handle: ");
//     Serial.println(json);
//     // return json;
//     return "{\"status\" : \"ok\", \"data\" : \"" + json + "\"}";
// }
// String handleMicSensytivity(uint8_t *data, size_t len)
// {
//     data[len] = '\0';
//     String json = (char *)data;

//     DynamicJsonDocument doc(JSON_OBJECT_SIZE(2) + 350);
//     DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

//     if (error)
//     { // Test if parsing succeeds.
//         Serial.print(F("deserializeJson() failed: "));
//         Serial.println(error.f_str());
//         return "deserializeJson error";
//     }
//     micSensytivity = int(doc["micSens"]);
//     preferences.begin("settings");
//     preferences.putInt("micSensytivity", micSensytivity);
//     preferences.end();
//     Serial.print("micSensytivity handle: ");
//     Serial.println(json);
//     // return json;
//     return "{\"status\" : \"ok\", \"data\" : \"" + json + "\"}";
// }
// String handleStripSpeedUpdate(uint8_t *data, size_t len)
// {
//     data[len] = '\0';
//     String json = (char *)data;

//     DynamicJsonDocument doc(JSON_OBJECT_SIZE(2) + 350);
//     DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

//     if (error)
//     { // Test if parsing succeeds.
//         Serial.print(F("deserializeJson() failed: "));
//         Serial.println(error.f_str());
//         return "deserializeJson error";
//     }
//     setSpeedStripe(int(doc["stripeSpeed"]));
//     // stripeSpeed = int(doc["stripeSpeed"]);

//     Serial.print("stripeSpeed handle: ");
//     Serial.println(json);
//     return "{\"status\" : \"ok\", \"data\" : \"" + json + "\"}";
// }
// String handleMatrixSpeedUpdate(uint8_t *data, size_t len)
// {
//     data[len] = '\0';
//     String json = (char *)data;

//     DynamicJsonDocument doc(JSON_OBJECT_SIZE(2) + 350);
//     DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

//     if (error)
//     { // Test if parsing succeeds.
//         Serial.print(F("deserializeJson() failed: "));
//         Serial.println(error.f_str());
//         return "deserializeJson error";
//     }

//     setSpeedMatrix(int(doc["matrixSpeed"]));
//     Serial.print("matrixSpeed handle: ");
//     Serial.println(json);
//     Serial.print("mapped: ");
//     Serial.println(map(matrixSpeed, 0, 255, 2000, 0));
//     return "{\"status\" : \"ok\", \"data\" : \"" + json + "\"}";
// }
// String handleStripBrightnessUpdate(uint8_t *data, size_t len)
// {
//     data[len] = '\0';
//     String json = (char *)data;

//     DynamicJsonDocument doc(JSON_OBJECT_SIZE(2) + 350);
//     DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

//     if (error)
//     { // Test if parsing succeeds.
//         Serial.print(F("deserializeJson() failed: "));
//         Serial.println(error.f_str());
//         return "deserializeJson error";
//     }
//     // stripBrightness = int(doc["Sbrightness"]);
//     //  BRIGHTNESS = int(doc["brightness"]);
//     setBrightStripe(int(doc["Sbrightness"]));
//     Serial.print("brightness handle: ");
//     Serial.println(json);
//     // return json;
//     return "{\"status\" : \"ok\", \"data\" : \"" + json + "\"}";
// }
// String handleMatrixBrightnessUpdate(uint8_t *data, size_t len)
// {
//     data[len] = '\0';
//     String json = (char *)data;

//     DynamicJsonDocument doc(JSON_OBJECT_SIZE(2) + 350);
//     DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

//     if (error)
//     { // Test if parsing succeeds.
//         Serial.print(F("deserializeJson() failed: "));
//         Serial.println(error.f_str());
//         return "deserializeJson error";
//     }
//     // matrixBrightness = int(doc["Mbrightness"]);
//     setBrightMatrix(int(doc["Mbrightness"]));
//     Serial.print("brightness handle: ");
//     Serial.println(json);
//     // return json;
//     return "{\"status\" : \"ok\", \"data\" : \"" + json + "\"}";
// }
// String handleClockColor(uint8_t *data, size_t len)
// {
//     data[len] = '\0';
//     String json = (char *)data;

//     DynamicJsonDocument doc(JSON_OBJECT_SIZE(2) + 350);
//     DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

//     if (error)
//     { // Test if parsing succeeds.
//         Serial.print(F("deserializeJson() failed: "));
//         Serial.println(error.f_str());
//         return "deserializeJson error";
//     }
//     String color = doc["clockColor"];

//     clockColor = stringToCRGB(color);
//     preferences.begin("settings", false);
//     preferences.putString("clockColor", color);
//     preferences.end();

//     Serial.print("clockColor handle: ");
//     Serial.println(json);
//     // return json;
//     return "{\"status\" : \"ok\", \"clockColor\" : \"" + color + "\"}";
// }
// String handleOnOffClock(uint8_t *data, size_t len)
// {
//     data[len] = '\0';
//     String json = (char *)data;

//     DynamicJsonDocument doc(JSON_OBJECT_SIZE(2) + 350);
//     DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

//     if (error)
//     { // Test if parsing succeeds.
//         Serial.print(F("deserializeJson() failed: "));
//         Serial.println(error.f_str());
//         return "deserializeJson error";
//     }
//     String tempOnOffClock = doc["onOffClock"];
//     if (tempOnOffClock == "on")
//     {
//         clockOnOff = true;
//     }
//     else
//     {
//         clockOnOff = false;
//     }
//     preferences.begin("settings", false);
//     preferences.putBool("clockOnOff", clockOnOff);
//     preferences.end();
//     String onoff = clockOnOff ? "on" : "off";
//     Serial.print("ON-OFF-Clock handle: ");
//     Serial.println(json);
//     // return json;
//     return "{\"status\" : \"ok\", \"onOffClock\" : \"" + onoff + "\"}";
// }
// String handlepaletteTime(uint8_t *data, size_t len)
// {
//     data[len] = '\0';
//     String json = (char *)data;

//     DynamicJsonDocument doc(JSON_OBJECT_SIZE(2) + 350);
//     DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

//     if (error)
//     { // Test if parsing succeeds.
//         Serial.print(F("deserializeJson() failed: "));
//         Serial.println(error.f_str());
//         return "deserializeJson error";
//     }
//     paletteTime = int(doc["paletteTime"]); // 1
//     preferences.begin("settings", false);
//     preferences.putInt("paletteTime", paletteTime);
//     preferences.end();

//     Serial.print("paletteTime handle: ");
//     Serial.println(json);
//     // return json;
//     return "{\"status\" : \"ok\", \"data\" : \"" + json + "\"}";
// }
// String handlePaletteUpdate(uint8_t *data, size_t len)
// {
//     data[len] = '\0';
//     String json = (char *)data;

//     DynamicJsonDocument doc(JSON_OBJECT_SIZE(2) + 350);
//     DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

//     if (error)
//     { // Test if parsing succeeds.
//         Serial.print(F("deserializeJson() failed: "));
//         Serial.println(error.f_str());
//         return "deserializeJson error";
//     }

//     String paletteName = doc["palette"];
//     int patterns;
//     if (paletteName == "prevStripe")
//     {
//         if (autoPalStr == 0)
//         {
//             prevPaletteStripe();
//         }
//         else
//         {
//             return "{\"status\" : \"ok\",  \"paletteStripeName\" : \"AUTO CHANGE - " + paletteList[currentPaletteStripeIndex].Name + "\"}";
//         }
//         return "{\"status\" : \"ok\",  \"paletteStripeName\" : \"" + paletteList[currentPaletteStripeIndex].Name + "\"}";
//     }
//     else if (paletteName == "nextStripe")
//     {
//         if (autoPalStr == 0)
//         {
//             nextPaletteStripe(false);
//         }
//         else
//         {
//             return "{\"status\" : \"ok\",  \"paletteStripeName\" : \"AUTO CHANGE - " + paletteList[currentPaletteStripeIndex].Name + "\"}";
//         }
//         return "{\"status\" : \"ok\",  \"paletteStripeName\" : \"" + paletteList[currentPaletteStripeIndex].Name + "\"}";
//     }
//     else if (paletteName == "prevMatrix")
//     {
//         if (autoPalMat == 0)
//         {
//             prevPaletteMatrix();
//         }
//         else
//         {
//             return "{\"status\" : \"ok\",  \"paletteMatrixName\" : \"AUTO CHANGE - " + paletteList[currentPaletteMatrixIndex].Name + "\"}";
//         }
//         return "{\"status\" : \"ok\",  \"paletteMatrixName\" : \"" + paletteList[currentPaletteMatrixIndex].Name + "\"}";
//     }
//     else if (paletteName == "nextMatrix")
//     {
//         if (autoPalMat == 0)
//         {
//             nextPaletteMatrix(false);
//         }
//         else
//         {
//             return "{\"status\" : \"ok\",  \"paletteMatrixName\" : \"AUTO CHANGE - " + paletteList[currentPaletteMatrixIndex].Name + "\"}";
//         }
//         return "{\"status\" : \"ok\",  \"paletteMatrixName\" : \"" + paletteList[currentPaletteMatrixIndex].Name + "\"}";
//     }
//     preferences.end();
//     Serial.print("palette handle: ");
//     Serial.println(json);
//     return "{\"status\" : \"ok\",  \"data\" : \"" + json + "\"}";
// }
// String handlePatternsUpdate(uint8_t *data, size_t len)
// {
//     data[len] = '\0';
//     String json = (char *)data;

//     DynamicJsonDocument doc(JSON_OBJECT_SIZE(2) + 350);
//     DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

//     if (error)
//     { // Test if parsing succeeds.
//         Serial.print(F("deserializeJson() failed: "));
//         Serial.println(error.f_str());
//         return "deserializeJson error";
//     }

//     /*
//     0 = prevStripe
//     1 = nextStripe
//     2 = prevMatrix
//     3 = nextMatrix
//     */
//     preferences.begin("settings");
//     String patternsName = doc["patterns"];
//     int patterns;
//     bool isAudio;
//     String audioReactive;
//     if (patternsName == "prevStripe")
//     {
//         prevPatternStripe();
//         isAudioStripe ? audioReactive = "AUDIO REACTIVE" : audioReactive = "STATIC";
//         return "{\"status\" : \"ok\", \"isAudio\" : \"" + audioReactive + "\",\"curPatStr\" : \"" + CurrentStripePatternNumber + "\",\"maxPatStr\" : \"" + StripePatternsAmount + "\", \"patternStripe\" : \"" + String(patternStripe) + "\", \"patternStripeName\" : \"" + patternsStripe[CurrentStripePatternNumber].name + "\"}";
//     }
//     else if (patternsName == "nextStripe")
//     {
//         nextPatternStripe();
//         isAudioStripe ? audioReactive = "AUDIO REACTIVE" : audioReactive = "STATIC";
//         return "{\"status\" : \"ok\", \"isAudio\" : \"" + audioReactive + "\",\"curPatStr\" : \"" + CurrentStripePatternNumber + "\",\"maxPatStr\" : \"" + StripePatternsAmount + "\", \"patternStripe\" : \"" + String(patternStripe) + "\", \"patternStripeName\" : \"" + patternsStripe[CurrentStripePatternNumber].name + "\"}";
//     }
//     else if (patternsName == "prevMatrix")
//     {
//         prevPatternMatrix();
//         isAudioMatrix ? audioReactive = "AUDIO REACTIVE" : audioReactive = "STATIC";

//         return "{\"status\" : \"ok\", \"isAudio\" : \"" + audioReactive + "\",\"curPatMat\" : \"" + CurrentMatrixPatternNumber + "\",\"maxPatMat\" : \"" + MatrixPatternsAmount + "\", \"patternMatrix\" : \"" + String(patternMatrix) + "\", \"patternMatrixName\" : \"" + patternsMatrix[CurrentMatrixPatternNumber].name + "\"}";
//     }
//     else if (patternsName == "nextMatrix")
//     {
//         nextPatternMatrix();
//         isAudioMatrix ? audioReactive = "AUDIO REACTIVE" : audioReactive = "STATIC";
//         return "{\"status\" : \"ok\", \"isAudio\" : \"" + audioReactive + "\",\"curPatMat\" : \"" + CurrentMatrixPatternNumber + "\",\"maxPatMat\" : \"" + MatrixPatternsAmount + "\", \"patternMatrix\" : \"" + String(patternMatrix) + "\", \"patternMatrixName\" : \"" + patternsMatrix[CurrentMatrixPatternNumber].name + "\"}";
//     }

//     Serial.print("patterns handle: ");
//     Serial.println(json);
//     return "{\"status\" : \"ok\", \"patternStripe\" : \"" + String(patternStripe) + "\", \"patternMatrix\" : \"" + String(patternMatrix) + "\"}";
// }

// String handleShowMessage(uint8_t *data, size_t len)
// {
//     data[len] = '\0';
//     String json = (char *)data;

//     DynamicJsonDocument doc(JSON_OBJECT_SIZE(2) + 350);
//     DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

//     if (error)
//     { // Test if parsing succeeds.
//         Serial.print(F("deserializeJson() failed: "));
//         Serial.println(error.f_str());
//         return "deserializeJson error";
//     }

//     // String message = doc["message"].as<String>();
//     runString(welcomeMessage, CRGB::Green, 19);
//     Serial.print("shoiw message handle: ");
//     Serial.println(json);

//     return "{\"status\" : \"ok\", \"data\" : \"" + json + "\"}";
// }
// String handleMessageUpdate(uint8_t *data, size_t len)
// {
//     data[len] = '\0';
//     String json = (char *)data;

//     DynamicJsonDocument doc(JSON_OBJECT_SIZE(2) + 350);
//     DeserializationError error = deserializeJson(doc, json); // Deserialize the JSON document

//     if (error)
//     { // Test if parsing succeeds.
//         Serial.print(F("deserializeJson() failed: "));
//         Serial.println(error.f_str());
//         return "deserializeJson error";
//     }

//     welcomeMessage = doc["message"].as<String>();

//     Serial.print("Welcome message handle: ");
//     Serial.println(json);

//     preferences.begin("settings");
//     preferences.putString("WMessage", welcomeMessage);
//     preferences.end();
//     // return json;
//     return "{\"status\" : \"ok\", \"data\" : \"" + json + "\"}";
// }
// void notFound(AsyncWebServerRequest *request)
// {
//     request->send(404, "text/plain", "Not found");
// }
// void initWebServer()
// {
//     server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
//               { request->send(SPIFFS, "/index.html", String(), false, processor); });
//     server.on("/matrix", HTTP_GET, [](AsyncWebServerRequest *request)
//               { request->send(SPIFFS, "/matrix.html", String(), false, processor); });
//     server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request)
//               { request->send(SPIFFS, "/settings.html", String(), false, processor); });
//     server.on("/main.css", HTTP_GET, [](AsyncWebServerRequest *request)
//               { request->send(SPIFFS, "/main.css", "text/css"); });

//     server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request)
//               { request->send(SPIFFS, "/main.js", "text/css"); });

//     server.on(
//         "/patterns", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
//         [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
//         {
//             Serial.print("server.on patterns");
//             String myResponse = handlePatternsUpdate(data, len);
//             request->send(200, "text/plain", myResponse);
//         });
//     server.on(
//         "/palette", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
//         [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
//         {
//             Serial.print("server.on palette");
//             String myResponse = handlePaletteUpdate(data, len);
//             request->send(200, "text/plain", myResponse);
//         });

//     server.on(
//         "/paletteTime", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
//         [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
//         {
//             Serial.print("server.on palette time");
//             String myResponse = handlepaletteTime(data, len);
//             request->send(200, "text/plain", myResponse);
//         });

//     server.on(
//         "/message", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
//         [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
//         {
//             String myResponse = handleMessageUpdate(data, len);
//             request->send(200, "text/plain", myResponse);
//         });

//     server.on(
//         "/onoffClock", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
//         [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
//         {
//             String myResponse = handleOnOffClock(data, len);
//             request->send(200, "text/plain", myResponse);
//         });
//     server.on(
//         "/clockColor", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
//         [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
//         {
//             String myResponse = handleClockColor(data, len);
//             request->send(200, "text/plain", myResponse);
//         });
//     server.on(
//         "/showMessage", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
//         [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
//         {
//             String myResponse = handleShowMessage(data, len);
//             request->send(200, "text/plain", myResponse);
//         });
//     server.on(
//         "/sBright", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
//         [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
//         {
//             String myResponse = handleStripBrightnessUpdate(data, len);
//             request->send(200, "text/plain", myResponse);
//         });
//     server.on(
//         "/mBright", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
//         [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
//         {
//             String myResponse = handleMatrixBrightnessUpdate(data, len);
//             request->send(200, "text/plain", myResponse);
//         });
//     server.on(
//         "/micSens", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
//         [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
//         {
//             String myResponse = handleMicSensytivity(data, len);
//             request->send(200, "text/plain", myResponse);
//         });
//     server.on(
//         "/micNoise", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
//         [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
//         {
//             String myResponse = handleMicNoise(data, len);
//             request->send(200, "text/plain", myResponse);
//         });
//     server.on(
//         "/sSpeed", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
//         [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
//         {
//             String myResponse = handleStripSpeedUpdate(data, len);
//             request->send(200, "text/plain", myResponse);
//         });
//     server.on(
//         "/mSpeed", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
//         [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
//         {
//             String myResponse = handleMatrixSpeedUpdate(data, len);
//             request->send(200, "text/plain", myResponse);
//         });
//     server.on(
//         "/checkBoxS", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
//         [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
//         {
//             String myResponse = handleAutopaletteStripeUpdate(data, len);
//             request->send(200, "text/plain", myResponse);
//         });
//     server.on(
//         "/checkBoxM", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
//         [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
//         {
//             String myResponse = handleAutopaletteMatrixUpdate(data, len);
//             request->send(200, "text/plain", myResponse);
//         });

//     server.onNotFound(notFound);

//     server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request)
//               { request->send(SPIFFS, "/favicon.png", "image/png"); });
//     server.on("/finger.png", HTTP_GET, [](AsyncWebServerRequest *request)
//               { request->send(SPIFFS, "/finger.png.png", "image/png"); });
//     // AsyncElegantOTA.begin(&server); //* OTA - Start ElegantOTA
//     server.begin();
//     Serial.println("SERVER STARTED");
// }

// void RunAPmode()
// {
//     WiFi.disconnect(true); // End All connections.
//     WiFi.mode(WIFI_AP);
//     WiFi.softAP(ssidAP, passwordAP);                               // Start ACCESSPOINT MODE with basic credentials
//     IPAddress IP = WiFi.softAPIP();                                // GET THE ACCESSPOINT IP
//     Serial.println("The IP of the settings page is: 192.168.4.1"); // SHOW IP IN SERIAL MONITOR
//     // Serial.println(WiFi.localIP());
//     // Make sure we have something to store our preferences in
//     //  server.serveStatic("/", SPIFFS, "/").setDefaultFile("indexAP.html");
//     server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { // The Home page so to say.
//         request->send(SPIFFS, "/indexAP.html", "text/html");
//     });
//     server.on("/main.css", HTTP_GET, [](AsyncWebServerRequest *request)
//               { request->send(SPIFFS, "/main.css", "text/css"); });

//     server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request)
//               { request->send(SPIFFS, "/main.js", "text/css"); });
//     server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) { // WHEN SOMEONE SUBMITS SOMETHING.... Like the credentials :)
//         String inputMessage;
//         String inputMessage2;
//         String inputMessage3;
//         const char *PARAM_WIFI = "SSIDname";
//         const char *PARAM_PWD = "SSIDpwd";
//         preferences.begin("settings", false);
//         if (request->hasParam(PARAM_WIFI))
//         {
//             inputMessage = request->getParam(PARAM_WIFI)->value();
//             ssid = inputMessage;
//             preferences.putString("ssid", ssid);
//             inputMessage2 = request->getParam(PARAM_PWD)->value();
//             pass = inputMessage2;
//             preferences.putString("password", pass);
//             inputMessage3 = "Restarting and using new credentials";
//             Serial.println(inputMessage);
//             Serial.println(inputMessage2);
//             Serial.println(inputMessage3);
//             ESP.restart();
//         }
//         else if (request->hasParam(PARAM_PWD))
//         {
//             inputMessage = request->getParam(PARAM_PWD)->value();
//             pass = inputMessage;
//             preferences.putString("password", pass);
//         }
//         else
//         {
//             inputMessage = "Restarting and using new credentials";
//             ESP.restart();
//         }
//         // This prints the submitted variable on the serial monitor.. as a check
//         request->send(200, "text/text", inputMessage);
//     });
//     preferences.end();

//     server.onNotFound(notFound);
//     IPAddress myIP = WiFi.softAPIP();
//     Serial.print("AP IP address: ");
//     Serial.println(myIP);
//     server.begin();
//     Serial.print("AP mode runs on core: ");
//     Serial.println(xPortGetCoreID());
// }
// boolean connectToNetwork(String s, String p)
// {
//     const char *ssid = s.c_str();
//     const char *password = p.c_str();

//     Serial.print("ACCESSING WIFI: ");
//     Serial.println(ssid);
//     WiFi.begin(ssid, password);

//     int timeout = 0;
//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(2000);
//         Serial.println("Connecting to WiFi..");
//         if (timeout == 5)
//         {
//             return false;
//             break;
//         }
//         Serial.println(".");
//         timeout++;
//     }
//     Serial.println(WiFi.localIP());
//     return true;
// } // network()

// void listDir(fs::FS &fs, const char *dirname, uint8_t levels)
// {
//     Serial.printf("Listing directory: %s\r\n", dirname);

//     File root = fs.open(dirname);
//     if (!root)
//     {
//         Serial.println("- failed to open directory");
//         return;
//     }
//     if (!root.isDirectory())
//     {
//         Serial.println(" - not a directory");
//         return;
//     }

//     File file = root.openNextFile();
//     while (file)
//     {
//         if (file.isDirectory())
//         {
//             Serial.print("  DIR : ");
//             Serial.println(file.name());
//             if (levels)
//             {
//                 listDir(fs, file.path(), levels - 1);
//             }
//         }
//         else
//         {
//             Serial.print("  FILE: ");
//             Serial.print(file.name());
//             Serial.print("\tSIZE: ");
//             Serial.println(file.size());
//         }
//         file = root.openNextFile();
//     }
// }