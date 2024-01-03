#include "button.h"

#define DEBOUNCE_DELAY 15 // Milliseconds

// Button variables
bool isPressed = false;
ButtonColor pressedButtonColor;
byte buttons[] = { A0, A1, A2, A3 };
#define BUTTON_COUNT sizeof(buttons)
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
    byte buttonPress = digitalRead(buttons[n]);

    if (buttonPress != lastButtonPressStates[n]) lastDebounceTime[n] = currentTime;

    if (
      (currentTime - lastDebounceTime[n]) > DEBOUNCE_DELAY &&
      buttonPressStates[n] != buttonPress
    ) {
      buttonPressStates[n] = buttonPress;
      if (buttonPress == LOW) {    // button pressed
        isPressed = true;
        pressedButtonColor = getButtonColorByIndex(n);
      }
    }
    lastButtonPressStates[n] = buttonPress;
  }
}

// Returns true if any of the buttons are pressed
bool isButtonPressed() {
  return isPressed;
}

void resetButtonPress() {
  isPressed = false;
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
