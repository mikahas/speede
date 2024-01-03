#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>

// Used for menu interactions
enum ButtonColor: byte { BUTTON_RED, BUTTON_YELLOW, BUTTON_GREEN, BUTTON_BLUE };

void setupButtons();
void handleButtons();
bool isButtonPressed();
void resetButtonPress();
ButtonColor getPressedButtonColor();
ButtonColor getButtonColorByIndex(byte index);
byte getRandomColorIndex();

#endif