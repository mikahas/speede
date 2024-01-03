#include "speede.h"
#include "button_leds.h"
#include "game_speed.h"
#include "button.h"
#include "display.h"
#include "game_state.h"

void setup() {

  // NOTE: makes the 7 segment flicker
  Serial.begin(9600);
  Serial.println("Spedebug");

  setupDisplay();
  setupButtons();
  setupLEDs();
  setupPlayer();
  setupMenu();

  // Generate a random seed from reading a value from unconnected pin 
  randomSeed(analogRead(UNCONNECTED_RANDOM_PIN));
}

void loop() {
  
  handleButtons();
  handleNote(); // Used for playing single notes
  handlePiece(); // Used for playing longer game Chime
  handleScrollText();

  switch (getGameState()) {
    case GAME_LOBBY:
      handleGameLobby();
      break;
    case GAME_SPEED:
      handleSpeedGame();
      break;
    case GAME_OVER:
      // TODO: Congratulate on new high score when needed
      if (isButtonPressed) setGameState(GAME_LOBBY);
      break;
    case GAME_DEMO:
      handleDemo(); // Just blink some LEDs!
      break;
    case GAME_HIGH_SCORE:
      // TODO: show high score
      break;
    // TODO: memory game

  }

  refreshDisplay();
}
