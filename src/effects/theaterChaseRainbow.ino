
long delayTC = 0;
void theaterChaseRainbow()
{
    if (millis() - delayTC > patternInterval)
    {
        for (int i = 0; i < allPixelsAmount; i += 3)
        {
            SetMyLED(i + pixelQueue, Wheel((i + pixelCycle) % 255)); //  Update delay time
        }
        showAllStrips();
        for (int i = 0; i < allPixelsAmount; i += 3)
        {
            SetMyLED(i + pixelQueue, 0, 0, 0); //  Update delay time
        }
        pixelQueue++; //  Advance current queue
        pixelCycle++; //  Advance current cycle
        if (pixelQueue >= 3)
            pixelQueue = 0; //  Loop
        if (pixelCycle >= 256)
            pixelCycle = 0; //  Loop
        delayTC = millis();
    }
}