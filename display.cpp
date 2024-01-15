#include "display.h"

#define SHIFT_PIN_DS   13
#define SHIFT_PIN_STCP 12
#define SHIFT_PIN_SHCP 11

// SevSeg sevseg;
SevSegShift sevseg(SHIFT_PIN_DS, SHIFT_PIN_SHCP, SHIFT_PIN_STCP);

unsigned long scrollTextTimer;
byte scrollCursor;
char *scrollMessage;
bool enableScrolling = false;

void setupDisplay() {
  // Setup display
  byte numDigits = 4;

  // Arduino pins (no shift registers)
  // byte digitPins[] = { 2, 3, 4, 5 };
  // byte segmentPins[] = { 6, 7, 8, 9, 10, 11, 12, 13 };

  // Shift register pins
  byte digitPins[] = {1, 4, 5, 8+1}; // of ShiftRegister(s) | 8+x (2nd Register)
  byte segmentPins[] = {2, 6, 8+3, 8+5, 8+6, 3, 8+2,  8+4}; // of Shiftregister(s) | 8+x (2nd Register)

  bool resistorsOnSegments = true; // 'false' means resistors are on digit pins
  // byte hardwareConfig = COMMON_ANODE;
  byte hardwareConfig = P_TRANSISTORS;

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
