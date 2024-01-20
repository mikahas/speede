#include "game_state.h"

GameMenu gameState = GAME_LOBBY; // Start with the lobby

GameMenu getGameState() {
  return gameState;
}

// Demo stuff
unsigned long gameStateTimer;
// int demoNotes[] = { NOTE_A4, NOTE_B4, NOTE_C4, NOTE_D4 };
byte previousDemoColor;

void setupMenu() {
  setScrollText("   PUSH RED TO START - BLUE FOR HISCORE - HOLD BLUE TO RESET HISCORE -");
  gameStateTimer = millis();
}

void setGameState(GameMenu state) {
  gameStateTimer = millis();
  gameState = state;
}

void handleGameLobby() {
  unsigned long currentTime = millis();

  if (isButtonLongPressed()) {
    resetButtonLongPress();
    switch(getPressedButtonColor()) {
      case ButtonColor::BUTTON_BLUE:
        resetHighScore();
        break;
    }
  }

  if (isButtonPressed()) {
    resetButtonPress();
    stopScrolling(); // Always stop scrolling after any interaction

    switch(getPressedButtonColor()) {
      case ButtonColor::BUTTON_RED:
        initializeSpeedGame();
        break;
      // TODO: memory game
      // case ButtonColor::BUTTON_YELLOW:
      //   break;
      case ButtonColor::BUTTON_BLUE:
        char highScore[18]; // "    HISCORE: " + 1 to 4 numbers
        sprintf(highScore, "    HISCORE - %d", getHighScore());
        setScrollText(highScore);
        setGameState(GameMenu::GAME_HIGH_SCORE);
        break;
    }
  }
  // Do a demo after a while
  if ((currentTime - gameStateTimer) >= GENERAL_PAUSE_TIME * 10) {
    setGameState(GAME_DEMO);
  }

}

void checkButtonPress() {
  if (isButtonPressed() || isButtonLongPressed()) {
    // Do not reset button press, let the lobby handle it!
    setGameState(GAME_LOBBY);
  }
}

void handleDemo() {
  unsigned long currentTime = millis();

  checkButtonPress();

  if ((currentTime - gameStateTimer) >= INITIAL_REACTION_TIME) {
    byte nextRandomColor = getRandomColorIndex();
    highlightOneButtonLED(getButtonColorByIndex(nextRandomColor));
    // playNote(demoNotes[nextRandomColor], 100); // Please don't!

    previousDemoColor = nextRandomColor;
    gameStateTimer = currentTime;
  }

  if ((currentTime - gameStateTimer) >= INITIAL_REACTION_TIME * 2 / 3) {
    // Turn off the previous LED before turning on the next one
    turnOffLeds();
  }
}

void handleHighScore() {
  unsigned long currentTime = millis();
  // Just wait for input and show the text
  checkButtonPress();

  // Do a demo after a while. Should still keep scrolling the hiscore text.
  if ((currentTime - gameStateTimer) >= GENERAL_PAUSE_TIME * 10) {
    setGameState(GAME_DEMO);
  }
}