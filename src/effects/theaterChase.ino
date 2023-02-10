void theaterChase(uint32_t colorT)
{                                           // modified from Adafruit example to make it a state machine
    unsigned long currentMillis = millis(); // Start of sample window
    if (currentMillis - previousMillis > patternInterval)
    {
        static int j = 0, q = 0;
        static boolean on = true;
        if (on)
        {
            for (int i = 0; i < allPixelsAmount; i = i + 3)
            {
                SetMyLedHUE(i + q, Wheel(colorT)); // turn every third pixel on
                                                   /// SetMyLED(i + q, Wheel((i + j) % 255, 1));
            }
        }
        else
        {
            for (int i = 0; i < allPixelsAmount; i = i + 3)
            {
                SetMyLED(i + q, 0, 0, 0); // turn every third pixel off
            }
        }
        on = !on;        // toggel pixelse on or off for next time
        showAllStrips(); //  strip.show(); // display
        q++;             // update the q variable
        if (q >= 3)
        { // if it overflows reset it and update the J variable
            q = 0;
            j++;
            if (j >= 256)
                j = 0;
        }
        previousMillis = currentMillis; // Remember the time
    }
}