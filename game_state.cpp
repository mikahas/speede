#include "game_state.h"

GameMenu gameState = GAME_LOBBY; // Start with the lobby

GameMenu getGameState() {
  return gameState;
}

// Demo stuff
unsigned long menuDemoTimer;
// int demoNotes[] = { NOTE_A4, NOTE_B4, NOTE_C4, NOTE_D4 };
byte previousDemoColor;

void setupMenu() {
  setScrollText("   PUSH RED TO START");
  menuDemoTimer = millis();
}

void setGameState(GameMenu state) {
  menuDemoTimer = millis();
  gameState = state;
}

void handleGameLobby() {
  unsigned long currentTime = millis();
  if(isButtonPressed()) {
    resetButtonPress();
    stopScrolling(); // Always stop scrolling after any interaction

    switch(getPressedButtonColor()) {
      case ButtonColor::BUTTON_RED:
        initializeSpeedGame();
        break;
      // TODO: memory game
      // case ButtonColor::BUTTON_YELLOW:
      //   break;
    }
  }
  // Do a demo after a while
  if ((currentTime - menuDemoTimer) >= GENERAL_PAUSE_TIME * 10) {
    gameState = GAME_DEMO;
  }

}

void handleDemo() {
  unsigned long currentTime = millis();

  if (isButtonPressed()) {
    // Do not reset button press, let the lobby will handle it!
    menuDemoTimer = millis();
    setGameState(GAME_LOBBY);
    return;
  }

  if ((currentTime - menuDemoTimer) >= INITIAL_REACTION_TIME) {
    byte nextRandomColor = getRandomColorIndex();
    highlightOneButtonLED(getButtonColorByIndex(nextRandomColor));
    // playNote(demoNotes[nextRandomColor], 100); // Please don't!

    previousDemoColor = nextRandomColor;
    menuDemoTimer = currentTime;
  }

  if ((currentTime - menuDemoTimer) >= INITIAL_REACTION_TIME * 2 / 3) {
    // Turn off the previous LED before turning on the next one
    turnOffLeds();
  }
}