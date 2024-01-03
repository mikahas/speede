#ifndef SPEEDE_H
#define SPEEDE_H

// Maximum number of pending button presses. On unlimited genuine speed test this seems to be 50.
#define MAX_STACK 50

// Arduino MEGA 2560 pin, do not connect anything to this pin for better randomness!
#define UNCONNECTED_RANDOM_PIN 42

// Similar delay was used in Jaakko Kairus' speed game
#define INITIAL_REACTION_TIME 570.0 // Milliseconds

// If there's a delay, use this!
#define GENERAL_PAUSE_TIME 1337 // Milliseconds

// 220 - 250 should be just fine so user can read with ease but doesn't have to wait too long!
#define DISPLAY_SCROLL_SPEED 250 // Milliseconds

#endif