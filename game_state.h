#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "button.h"
#include "game_speed.h"

enum GameMenu: byte { GAME_LOBBY, GAME_SPEED, GAME_OVER, GAME_DEMO, GAME_HIGH_SCORE };

void setupMenu();
GameMenu getGameState();
void setGameState(GameMenu state);
void handleGameLobby();
void handleDemo();

#endif