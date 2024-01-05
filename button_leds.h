#ifndef BUTTON_LEDS_H
#define BUTTON_LEDS_H

#include <Arduino.h>

#include "button.h"

// Handler for LEDs attached to the buttons.

void setupLEDs();
void turnOffLeds();
void turnOnLeds();
void highlightOneButtonLED(ButtonColor color);
void setLEDMask(byte mask);

#endif