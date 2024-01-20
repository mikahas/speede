#ifndef NOTE_PLAYER_H
#define NOTE_PLAYER_H

#include <Arduino.h>

#include "pitches.h"
#include "game_state.h"

// #define BUZZER_PIN 30 // Arduino MEGA 2560 pin
#define BUZZER_PIN 3 // Arduino UNO

// Note durations, e.g. 1/8 = 0.125
#define NOTE_DURATION_SIXTEENTH 16
#define NOTE_DURATION_EIGHTH_TRIPLET 12
#define NOTE_DURATION_EIGHTH 8
#define NOTE_DURATION_EIGHTH_DOT 5.333 // 1/8 + 1/16 = 3/16 (= ~1/5.333)
#define NOTE_DURATION_QUARTER 4
#define NOTE_DURATION_QUARTER_DOT 2.667 // 1/4 + 1/8 = 3/8 (= ~1/2.667)
#define NOTE_DURATION_HALF 2
#define NOTE_DURATION_FULL 1

#define NOTE_REST 0

enum Chime: byte {
  EasterEgg,
  GameOver,
  NewHighScore,
  NewGame,
  InTheHallOfTheMountainKing
};

struct Note {
  int head; // Note to play
  float value; // How long a note should be held, duration
};

struct Piece {
  Note *notes;
  byte noteCount;
  int tempo;

  // NOTE: Using int for tempo. The fastest tempo on a label-released single that has received radio
  // play is the song Thousand by Moby, which at one point reaches 1015 BPM.
  // https://www.youtube.com/watch?v=vRJKOCmTXLo
};

void setupPlayer();
void playNote(unsigned int note, unsigned int duration);
void handleNote();
void playPiece(Chime chime);
void handlePiece();
int getTempoInMillis(int pieceTempo);

#endif