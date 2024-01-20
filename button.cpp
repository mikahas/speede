#include "button.h"

#define DEBOUNCE_DELAY 15 // Milliseconds
#define LONG_PRESS_DELAY 3000 // 3 seconds

// Button variables
bool isPressed = false;
bool resetLongPress = false;
ButtonColor pressedButtonColor;
byte buttons[] = { A0, A1, A2, A3 };
#define BUTTON_COUNT sizeof(buttons)
bool isLongPress[BUTTON_COUNT] = { false, false, false, false };
byte buttonPressStates[BUTTON_COUNT] = {}; // List of button press states
byte lastButtonPressStates[BUTTON_COUNT] = {}; // Save last button press states to a list for comparing it to a new button press

ButtonColor buttonColors[BUTTON_COUNT] = {
  ButtonColor::BUTTON_RED,
  ButtonColor::BUTTON_YELLOW,
  ButtonColor::BUTTON_GREEN,
  ButtonColor::BUTTON_BLUE
};
unsigned long lastDebounceTime[] = { 0, 0, 0, 0 };  // The last time the output pin was toggled
byte previousRandomColor;

void setupButtons() {
  for (byte n = 0; n < BUTTON_COUNT; n++)  {
    pinMode(buttons[n], INPUT_PULLUP);
    buttonPressStates[n] = digitalRead(buttons[n]);
  }
}

// Record button press and color of the button. Called in the main loop.
void handleButtons() {
  unsigned long currentTime = millis();
  for (byte n = 0; n < BUTTON_COUNT; n++)  {
    byte buttonPressState = digitalRead(buttons[n]);

    if (buttonPressState != lastButtonPressStates[n]) lastDebounceTime[n] = currentTime;

    // Quick press handling
    if ((currentTime - lastDebounceTime[n]) > DEBOUNCE_DELAY &&
      buttonPressStates[n] != buttonPressState
    ) {
      buttonPressStates[n] = buttonPressState;
      if (buttonPressState == LOW) {    // button pressed
        isPressed = true;
        pressedButtonColor = getButtonColorByIndex(n);
      }
    }

    // Long press handling
    if (currentTime - lastDebounceTime[n] > LONG_PRESS_DELAY &&
      buttonPressState == LOW && // Keep pressed
      isLongPress[n] == false
    ) {
      isLongPress[n] = true;
      // pressedButtonColor = getButtonColorByIndex(n);
    }

    // Reset long press
    if (buttonPressState == HIGH && // No longer pressed
      resetLongPress == true &&
      isLongPress[n] == true
    ) {
      resetLongPress = false;
      isLongPress[n] = false;
    }

    lastButtonPressStates[n] = buttonPressState;
  }
}

// Returns true if any of the buttons are pressed
bool isButtonPressed() {
  return isPressed;
}

// return true if any of the buttons are long pressed
bool isButtonLongPressed() {
  for (byte n = 0; n < BUTTON_COUNT; n++)  {
    if (isLongPress[n] && resetLongPress == false) return true;
  }
  return false;
}

void resetButtonPress() {
  isPressed = false;
}

void resetButtonLongPress() {
  // Wait for user to stop pressing the button
  resetLongPress = true;
}

ButtonColor getPressedButtonColor() {
  return pressedButtonColor;
}

ButtonColor getButtonColorByIndex(byte index) {
  if (index >= BUTTON_COUNT || index < 0) return ButtonColor::BUTTON_RED;
  return buttonColors[index];
}

// Index of four colors: red, yellow, green or blue
byte getRandomColorIndex() {
  byte nextRandomColor = random(0, 4); // Exclusive max, the random value is between 0 and 3
  // Do not light the same color again
  while(nextRandomColor == previousRandomColor) nextRandomColor = random(0, 4);
  previousRandomColor = nextRandomColor;
  return nextRandomColor;
}
