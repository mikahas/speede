#ifndef GAME_SPEED_H
#define GAME_SPEED_H

#include <Arduino.h>
#include <EEPROM.h>

#include "speede.h"
#include "button_leds.h"
#include "note_player.h"
#include "button.h"
#include "display.h"
#include "game_state.h"

// NOTE: The EEPROM memory has a specified life of 100,000 write/erase cycles
#define EEPROM_SPEED_HIGH_SCORE_ADDRESS 0

void setupSpeedGame();
void initializeSpeedGame();
void handleSpeedGame();
float getUpdatedReactionTime(float currentReactionTime);
void handleSpeedGameOver();
bool addToStack(ButtonColor nextColor);
bool isButtonValid();
void incrementPoints();
int getHighScore();
void setHighScore(int newScore);
void resetHighScore();

#endif