
long delayCW = 0;
void colorWipe(uint32_t colorW)
{
    if (millis() - delayCW > patternInterval)
    {
        //  Update delay time
        SetMyLedHUE(pixelCurrent, Wheel(colorW)); //  Set pixel's color (in RAM)
        showAllStrips();                          //  Update strip to match
        pixelCurrent++;                           //  Advance current pixel
        if (pixelCurrent >= allPixelsAmount)      //  Loop the pattern from the first LED
            pixelCurrent = 0;
        delayCW = millis();
    }
}