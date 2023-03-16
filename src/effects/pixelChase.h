
#pragma once

#include "Imports.h"

// A bunch of variables
int playerIndex = -1;
int playerIndexTrail = -1;
int playerDirection = 1;
float nextMove = 0;
float currentPlayerSpeed = 150;
unsigned long countdown = 0;
int enemyIndex = -1;
int coinIndex = -1;
int score = 0;
int bestScore = 0;
int lastScore = 0;
bool gameOver = false;

// AllOff();
void pixelChase()
{
    // Every cycle we need to tick the button state
    // buttonTAP.tick();
    Serial.println(" 1 ");
    // If the game is in game over state, exit loop early
    if (gameOver)
        return;
    Serial.println(" 2 ");
    // Set the pixel display state of the level
    // This sets the enemy position and the coin position
    SetLevel();
    Serial.println(" 3 ");
    // wait for a second for the player to get ready
    if (countdown > millis())
    {

        FastLED.show();
        return;
    }
    Serial.println(" 4 ");
    // All the player display, movement and game logic is in here
    DisplayPlayer();
    Serial.println(" 5 ");
    // This sends the updated pixel color to the hardware.
    FastLED.show();
    Serial.println(" 6 ");
}

// Clear the level, setting all pixels to black
void ClearLevel()
{
    for (int i = 0; i < NUM_LEDS_STRIPE; i++)
        stripe[i] = CRGB(0, 0, 0); // Moderately bright green color.

    FastLED.show();
}

// Show the best score in yellow and if the last score was less than the best, show that on top in red
void BestScore()
{
    // Best score in yellow
    for (int i = 0; i < NUM_LEDS_STRIPE; i++)
    {
        if (i < bestScore)
            stripe[i] = CRGB(255, 155, 0); // Moderately bright green color.
        else
            stripe[i] = CRGB(0, 0, 0);
    }

    // last score is less than best is in red
    if (lastScore < bestScore)
    {
        for (int i = 0; i < lastScore; i++)
            stripe[i] = CRGB(255, 0, 0); // Moderately bright green color.
    }
    FastLED.show();
}

// Game over animation
void GameOver()
{
    // First pass we animate the strip going red from the enemy position
    int a = enemyIndex;
    int b = enemyIndex;

    for (int i = 0; i < NUM_LEDS_STRIPE / 2; i++)
    {
        stripe[a] = CRGB(255, 0, 0); // Moderately bright green color.
        stripe[b] = CRGB(255, 0, 0); // Moderately bright green color.

        a = (a + 1) % NUM_LEDS_STRIPE;
        b--;
        if (b == -1)
            b = NUM_LEDS_STRIPE;

        FastLED.show();
        delay(20);
    }

    delay(100);

    // Second pass we animate the strip going back from the enemy position
    a = enemyIndex;
    b = enemyIndex;

    for (int i = 0; i < NUM_LEDS_STRIPE / 2; i++)
    {
        stripe[a] = CRGB(0, 0, 0); // Black
        stripe[b] = CRGB(0, 0, 0); // Black

        a = (a + 1) % NUM_LEDS_STRIPE;
        b--;
        if (b == -1)
            b = NUM_LEDS_STRIPE;

        FastLED.show();
        delay(20);
    }

    // Now we show the best score
    delay(100);
    BestScore();
}

// Setup the level including the postiion of the enemy and the coin
void SetLevel()
{
    // If the enemy position is -1 (has been reset)
    // Find a new position for the enemy
    if (enemyIndex < 0)
    {
        // I fthe player not playing, always start the enemy at the half strip position
        if (playerIndex < 0)
        {
            enemyIndex = NUM_LEDS_STRIPE / 2;
        }
        // The player is in the game, so make sure not to place the enemy on or too close to the player
        else
        {
            enemyIndex = random(0, NUM_LEDS_STRIPE);

            while (abs(enemyIndex - playerIndex) < (NUM_LEDS_STRIPE / 4))
                enemyIndex = random(0, NUM_LEDS_STRIPE);
        }
    }
    // If the coin position is -1 (has been reset)
    // Find a new position for the coin
    if (coinIndex < 0)
    {
        coinIndex = random(0, NUM_LEDS_STRIPE);

        // pick a coin position somewhere between the player and enemy
        while (abs(coinIndex - playerIndex) < 7 || (abs(coinIndex - enemyIndex) < 7))
            coinIndex = random(0, NUM_LEDS_STRIPE);
    }

    stripe[enemyIndex] = CRGB(255, 0, 0);
    stripe[coinIndex] = CRGB(255, 255, 0);
}

// This is where all the magic happens
// Player movement happens here as well as game logic for collecting coins or hitting the enemy
void DisplayPlayer()
{

    if (nextMove < millis())
    {
        nextMove = millis() + currentPlayerSpeed;

        // The player has a visual trail, so these next 2 if statements shows or clears the trail
        if (playerIndexTrail >= 0)
            stripe[playerIndexTrail] = CRGB(0, 0, 0);

        if (playerIndex >= 0)
        {
            stripe[playerIndex] = CRGB(0, 100, 0);
            playerIndexTrail = playerIndex;
        }

        // Move the player in their current direction
        playerIndex += playerDirection;

        // Wrap the player at the strip edges
        if (playerIndex < 0)
            playerIndex = NUM_LEDS_STRIPE - 1;
        else if (playerIndex == NUM_LEDS_STRIPE)
            playerIndex = 0;

        stripe[playerIndex] = CRGB(0, 255, 0);

        // Did the player hit the coin?
        // If so, increase the score, reset coin and enemy positions and clear the level
        // Next loop the SetLevel() will reset the enemy and coin
        // Player speed is also increased for every coin hit
        if (playerIndex == coinIndex)
        {
            enemyIndex = -1;
            coinIndex = -1;
            score++;
            currentPlayerSpeed = constrain(currentPlayerSpeed - 10, 50, 150);
            ClearLevel();
            stripe[playerIndex] = CRGB(0, 255, 0);
        }
        // Did the player hit the enemy?
        // Set the last/best score and call game over
        else if (playerIndex == enemyIndex)
        {
            lastScore = score;
            if (score >= bestScore)
                bestScore = score;

            GameOver();

            gameOver = true;
            enemyIndex = -1;
            coinIndex = -1;
            playerIndex = -1;
        }
    }
}

// Single button click
void singleClick()
{
    // No input until player is visible
    if (countdown > millis())
        return;

    // switch the player direction
    playerDirection = -playerDirection;
}

// Long button click
void longClick()
{
    // Switch game over state
    // If it was game over, start the game, otherwise cancel a game in progress
    gameOver = !gameOver;
    if (gameOver)
    {
        enemyIndex = -1;
        coinIndex = -1;
        playerIndex = -1;
        currentPlayerSpeed = 150;
        ClearLevel();
    }
    else
    {
        ClearLevel();
        score = 0;
        currentPlayerSpeed = 150;
        countdown = millis() + 2000;
    }
}
