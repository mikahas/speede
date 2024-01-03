#include "button_leds.h"

// Button LEDs
byte buttonLeds[] = { 22, 24, 26, 28 }; // Arduino MEGA 2560
#define LED_PIN_COUNT sizeof(buttonLeds)

// Port A pins in Arduino MEGA 2560
#define LED_RED       B00000001 // Pin 22
#define LED_YELLOW    B00000100 // Pin 24
#define LED_GREEN     B00010000 // Pin 26
#define LED_BLUE      B01000000 // Pin 28

#define LEDS_ALL_OFF  B00000000
#define LEDS_ALL_ON   B01010101

void setupLEDs() {
    for (unsigned n = 0; n < LED_PIN_COUNT; n++)  {
        pinMode(buttonLeds[n], OUTPUT);
    }

    // Do a little demo and test the masks
    setLEDMask(LED_RED);
    delay(150);
    setLEDMask(LED_RED | LED_YELLOW);
    delay(150);
    setLEDMask(LED_RED | LED_YELLOW | LED_GREEN);
    delay(150);
    setLEDMask(LED_RED | LED_YELLOW | LED_GREEN | LED_BLUE);

    delay(1000);
    turnOffLeds();
    delay(100);
}

byte getLEDColorMask(ButtonColor color) {
  switch (color) {
    case ButtonColor::BUTTON_RED:
      return LED_RED;
    case ButtonColor::BUTTON_YELLOW:
      return LED_YELLOW;
    case ButtonColor::BUTTON_GREEN:
      return LED_GREEN;
    case ButtonColor::BUTTON_BLUE:
      return LED_BLUE;
  }
  // Handle error, maybe turn on all LEDs instead?
  return LEDS_ALL_OFF;
}

void turnOffLeds() {
  setLEDMask(LEDS_ALL_OFF);
}

void turnOnLeds() {
  setLEDMask(LEDS_ALL_ON);
}

void highlightOneButtonLED(ButtonColor color) {
  setLEDMask(getLEDColorMask(color));
}

void setLEDMask(byte mask) {
  byte ledMask = B01010101; // BLUE, GREEN, YELLOW, RED
  PORTA = ledMask & mask; // Arduino mega 2560 Port A (pins 22-29)
}
