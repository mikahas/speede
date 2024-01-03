#include "note_player.h"

bool isPlaying = false;
bool hasNote = false;
unsigned int noteToPlay;
unsigned long noteTimer; // Milliseconds
unsigned long noteDuration;

// In the Hall of the Mountain King, 4/4
Note pieceNotes1[] = {
  { NOTE_B2, NOTE_DURATION_QUARTER },
  { NOTE_CS3, NOTE_DURATION_QUARTER },
  { NOTE_D3, NOTE_DURATION_QUARTER },
  { NOTE_E3, NOTE_DURATION_QUARTER },
  { NOTE_FS3, NOTE_DURATION_QUARTER },
  { NOTE_D3, NOTE_DURATION_QUARTER },
  { NOTE_FS3, NOTE_DURATION_HALF },

  { NOTE_F3, NOTE_DURATION_QUARTER },
  { NOTE_CS3, NOTE_DURATION_QUARTER },
  { NOTE_F3, NOTE_DURATION_HALF },
  { NOTE_E3, NOTE_DURATION_QUARTER },
  { NOTE_C3, NOTE_DURATION_QUARTER },
  { NOTE_E3, NOTE_DURATION_HALF },

  { NOTE_B2, NOTE_DURATION_QUARTER },
  { NOTE_CS3, NOTE_DURATION_QUARTER },
  { NOTE_D3, NOTE_DURATION_QUARTER },
  { NOTE_E3, NOTE_DURATION_QUARTER },
  { NOTE_FS3, NOTE_DURATION_QUARTER },
  { NOTE_D3, NOTE_DURATION_QUARTER },
  { NOTE_FS3, NOTE_DURATION_QUARTER },
  { NOTE_B3, NOTE_DURATION_QUARTER },

  { NOTE_A3, NOTE_DURATION_QUARTER },
  { NOTE_FS3, NOTE_DURATION_QUARTER },
  { NOTE_D3, NOTE_DURATION_QUARTER },
  { NOTE_FS3, NOTE_DURATION_QUARTER },
  { NOTE_A3, NOTE_DURATION_HALF },
  
};

Piece musicPiece1 = {
  pieceNotes1,
  sizeof(pieceNotes1) / sizeof(pieceNotes1[0]),
  138
};

// Easter egg song released in 1987
Note easterEggNotes[] = {
  
  // ...
  { NOTE_G2, NOTE_DURATION_SIXTEENTH },
  { NOTE_A2, NOTE_DURATION_SIXTEENTH },
  { NOTE_C3, NOTE_DURATION_SIXTEENTH },
  { NOTE_A2, NOTE_DURATION_SIXTEENTH },

  { NOTE_E3, NOTE_DURATION_EIGHTH_DOT },
  { NOTE_E3, NOTE_DURATION_EIGHTH_DOT },
  { NOTE_D3, NOTE_DURATION_EIGHTH },
  { NOTE_REST, NOTE_DURATION_EIGHTH },
  { NOTE_G2, NOTE_DURATION_SIXTEENTH },
  { NOTE_A2, NOTE_DURATION_SIXTEENTH },
  { NOTE_C3, NOTE_DURATION_SIXTEENTH },
  { NOTE_A2, NOTE_DURATION_SIXTEENTH },

  { NOTE_G3, NOTE_DURATION_QUARTER },
  { NOTE_B2, NOTE_DURATION_EIGHTH },
  { NOTE_C3, NOTE_DURATION_EIGHTH_DOT },
  { NOTE_B2, NOTE_DURATION_SIXTEENTH },
  { NOTE_A2, NOTE_DURATION_EIGHTH },
  { NOTE_G2, NOTE_DURATION_SIXTEENTH },
  { NOTE_A2, NOTE_DURATION_SIXTEENTH },
  { NOTE_C3, NOTE_DURATION_SIXTEENTH },
  { NOTE_A2, NOTE_DURATION_SIXTEENTH },

  { NOTE_C3, NOTE_DURATION_QUARTER },
  { NOTE_D3, NOTE_DURATION_EIGHTH },
  { NOTE_B2, NOTE_DURATION_EIGHTH_DOT },
  { NOTE_A2, NOTE_DURATION_SIXTEENTH },
  { NOTE_G2, NOTE_DURATION_EIGHTH_DOT },
  { NOTE_G2, NOTE_DURATION_EIGHTH },

  { NOTE_D3, NOTE_DURATION_QUARTER },
  { NOTE_C3, NOTE_DURATION_HALF },
  { NOTE_REST, NOTE_DURATION_QUARTER },
};

Piece easterEgg = {
  easterEggNotes,
  sizeof(easterEggNotes) / sizeof(easterEggNotes[0]),
  114
};

Note notesGameOver[] = {
  { NOTE_REST, NOTE_DURATION_QUARTER },
  { NOTE_D3, NOTE_DURATION_QUARTER },
  { NOTE_CS3, NOTE_DURATION_QUARTER },
  { NOTE_C3, NOTE_DURATION_QUARTER },

  { NOTE_B2, NOTE_DURATION_HALF },
  { NOTE_REST, NOTE_DURATION_HALF },
};

Piece pieceGameOver = {
  notesGameOver,
  sizeof(notesGameOver) / sizeof(notesGameOver[0]),
  175
};

float pieceTempo;
byte noteIndex;
byte noteCount;
Note *notes;

void setupPlayer() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void playNote(unsigned int note, unsigned int duration) {
  noTone(BUZZER_PIN); // Stop playing previous note? Maybe not needed, test how it sounds!
  noteTimer = millis();
  hasNote = true;
  noteToPlay = note;
  noteDuration = duration;
}

void handleNote() {
  unsigned long currentTime = millis();
  if (hasNote) {
    hasNote = false;
    tone(BUZZER_PIN, noteToPlay);
  }
  if ((currentTime - noteTimer) >= noteDuration) noTone(BUZZER_PIN);
}

void playPiece(Chime chime) {
  noTone(BUZZER_PIN); // Stop playing the previous note
  noteDuration = 0;
  noteIndex = 0;
  isPlaying = true;
  switch (chime) {
    case Chime::GameOver:
      notes = pieceGameOver.notes;
      noteCount = pieceGameOver.noteCount;
      pieceTempo = getTempoInMillis(pieceGameOver.tempo);
      break;
    case Chime::EasterEgg:
      notes = easterEgg.notes;
      noteCount = easterEgg.noteCount;
      pieceTempo = getTempoInMillis(easterEgg.tempo);
      break;
    default:
      isPlaying = false;
  }
  noteTimer = millis();
}

// Loop through the piece
void handlePiece() {
  if (!isPlaying) return;

  unsigned long currentTime = millis();

  // Wait until the last note has played and end the loop
  if ((currentTime - noteTimer) >= noteDuration && noteIndex >= noteCount - 1) {
    noTone(BUZZER_PIN);
    isPlaying = false;
  };

  // Play the piece piece by piece
  if ((currentTime - noteTimer) >= noteDuration  && noteIndex < noteCount) {
    if (notes[noteIndex].head == NOTE_REST) noTone(BUZZER_PIN);
    else tone(BUZZER_PIN, notes[noteIndex].head);
    noteDuration = pieceTempo / notes[noteIndex].value;
    noteTimer = currentTime;
    noteIndex++;
  }

  // Staccato
  // if ((currentTime - noteTimer) >= noteDuration * 0.7) noTone(BUZZER_PIN);

  // Differentiate notes from each other for just a little bit
  if ((currentTime - noteTimer) >= noteDuration * 0.95) noTone(BUZZER_PIN);

}

// Duration of one whole note in milliseconds, "tempo"
int getTempoInMillis(int bpm) {
  return ( 1.0 / ( bpm / 60.0 ) ) * 4.0 * 1000.0;
}