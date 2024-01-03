#include "display.h"

SevSeg sevseg;

unsigned long scrollTextTimer;
byte scrollCursor;
char *scrollMessage;
bool enableScrolling = false;

void setupDisplay() {
  // Setup display
  byte numDigits = 4;
  byte digitPins[] = { 2, 3, 4, 5 };
  byte segmentPins[] = { 6, 7, 8, 9, 10, 11, 12, 13 };
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE;
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(50);
}

void setDisplayNumber(int number) {
  sevseg.setNumber(number, -1);
}

void setScrollText(char *text) {
  scrollCursor = 0;
  scrollMessage = text;
  enableScrolling = true;
  scrollTextTimer = millis();
}

void stopScrolling() {
  enableScrolling = false;
}

void handleScrollText() {
  if (!enableScrolling) return;

  unsigned long currentTime = millis();

  if ((currentTime - scrollTextTimer) >= DISPLAY_SCROLL_SPEED) {
    sevseg.setChars(&scrollMessage[scrollCursor]); // NOTE: is this really allowed?
    scrollCursor++;

    // Infinite scroll untill stopScrolling() is called
    if (scrollCursor > strlen(scrollMessage)) scrollCursor = 0;

    scrollTextTimer = currentTime;
  }
}

void refreshDisplay() {
  // Program must run the refreshDisplay() function repeatedly to display the number.
  // Warning: Any calls to delay() will interfere with the display.
  sevseg.refreshDisplay();
}
