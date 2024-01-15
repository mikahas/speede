#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

#include "SevSegShift.h"
#include "speede.h"

void setupDisplay();
void setDisplayNumber(int number);
void setScrollText(char *text);
void stopScrolling();
void handleScrollText();
void refreshDisplay();

#endif