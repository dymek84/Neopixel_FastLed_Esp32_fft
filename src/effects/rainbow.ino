void rainbow()
{
    unsigned long currentMillis = millis(); // Start of sample window
    if (currentMillis - previousMillis > patternInterval)
    {
        for (uint16_t i = 0; i < allPixelsAmount; i++)
        {
            SetMyLED(i, Wheel((i + pixelCycle) & 255)); //  Update delay time
        }
        showAllStrips(); //  Update strip to match
        pixelCycle++;    //  Advance current cycle
        if (pixelCycle >= 256)
            pixelCycle = 0;             //  Loop the cycle back to the begining
        previousMillis = currentMillis; // time for next change to the display
    }
}
