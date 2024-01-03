#ifndef GAME_SPEED_H
#define GAME_SPEED_H
#include <Arduino.h>
#include "speede.h"
#include "button_leds.h"
#include "note_player.h"
#include "button.h"
#include "display.h"
#include "game_state.h"

// Functionality
void initializeSpeedGame();
void handleSpeedGame();
float getUpdatedReactionTime(float currentReactionTime);
void handleSpeedGameOver();
bool addToStack(ButtonColor nextColor);
bool isButtonValid();
void incrementPoints();

#endif