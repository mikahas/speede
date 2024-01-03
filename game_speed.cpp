#include "game_speed.h"

unsigned long gameTimer; // Milliseconds
unsigned long gameMenuTimer; // Milliseconds
float reactionTime = INITIAL_REACTION_TIME;

// Stats
int speedGamePoints = 0;
ButtonColor buttonColorStack[MAX_STACK];
byte buttonColorStackLevel = 0;

// unsigned int buttonNotes[] = { NOTE_D4, NOTE_FS4, NOTE_A4, NOTE_C5 }; // D7
unsigned int buttonNotes[] = { NOTE_A4, NOTE_CS5, NOTE_E5, NOTE_GS5 }; // Amaj7

void initializeSpeedGame() {
  turnOffLeds();
  resetButtonPress();
  speedGamePoints = 0;
  setDisplayNumber(speedGamePoints);
  gameTimer = millis();
  reactionTime = INITIAL_REACTION_TIME;
  buttonColorStackLevel = 0;
  gameMenuTimer = millis();
  setGameState(GAME_SPEED);
}

// Loop the game
void handleSpeedGame() {
  unsigned long currentTime = millis();

  // Small delay before starting the game, TODO: do a chime?
  if ((currentTime - gameMenuTimer) < GENERAL_PAUSE_TIME) return;

  if (isButtonPressed()) {
    if (isButtonValid()) incrementPoints();
    else handleSpeedGameOver();
    resetButtonPress();
  }

  if (getGameState() == GAME_OVER) return;

  if ((currentTime - gameTimer) >= reactionTime) {
    byte nextRandomColor = getRandomColorIndex();
    playNote(buttonNotes[nextRandomColor], 100);

    if (!addToStack(getButtonColorByIndex(nextRandomColor))) {
      // Stack is full
      handleSpeedGameOver();
      return;
    }

    highlightOneButtonLED(getButtonColorByIndex(nextRandomColor));

    // Increase PANIC!!!1yks
    reactionTime = getUpdatedReactionTime(reactionTime);

    gameTimer = currentTime;
  }

  if ((currentTime - gameTimer) >= reactionTime * 2 / 3) {
    // Turn off the previous LED before turning on the next one
    turnOffLeds();
  }
}

// This is where the game reaction time is calculated!
float getUpdatedReactionTime(float currentReactionTime) {
  if (currentReactionTime > 399) return currentReactionTime * 993.0 / 1000.0;
  if (currentReactionTime > 326) return currentReactionTime * 996.0 / 1000.0;
  if (currentReactionTime > 192) return currentReactionTime * 9985.0 / 10000.0;
  currentReactionTime = currentReactionTime - 1;
  if (currentReactionTime < 100) return 100; // Limit minimum reaction time to 100 milliseconds
  return currentReactionTime; // Milliseconds
}

void handleSpeedGameOver() {
  turnOnLeds();
  if (speedGamePoints == 87) playPiece(Chime::EasterEgg);
  else playPiece(Chime::GameOver);
  // TODO: save high score if new record
  setGameState(GAME_OVER);
}

// Adds next color to stack or returns false if stack is full
bool addToStack(ButtonColor nextColor) {
  if (buttonColorStackLevel < MAX_STACK-1) {
    buttonColorStack[buttonColorStackLevel] = nextColor;
    buttonColorStackLevel++;
    return true;
  }
  return false; // Full stack
}

bool isButtonValid() {
  if (buttonColorStackLevel < 1) return false;
  if (buttonColorStack[0] != getPressedButtonColor()) return false;

  buttonColorStackLevel--;
  // Remove (shift) first element from stack
  for (byte n=0; n < buttonColorStackLevel; n++)
    buttonColorStack[n] = buttonColorStack[n+1];

  return true;
}

// Increments speed game points by one
void incrementPoints() {
  speedGamePoints++;
  // Max is 9999 due to display size limit
  if (speedGamePoints > 9999) speedGamePoints = 0; // Muhahaha!
  setDisplayNumber(speedGamePoints);
}