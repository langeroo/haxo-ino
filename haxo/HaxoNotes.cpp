/*
  HaxoNotes.cpp - Read the Haxophone key matrix, convert it to
  a bit-packed representation, and map it to a usable MIDI note.
*/

#include <Wire.h>
#include "HaxoNotes.h"

HaxoNotes::HaxoNotes() {}

void HaxoNotes::init() {
  // Initialize all pins
  for (int i = 0; i < _NUM_COLS; i++) {
      pinMode(_COLS[i], INPUT_PULLUP);
  }
  for (int i = 0; i < _NUM_ROWS; i++) {
      pinMode(_ROWS[i], OUTPUT);
      digitalWrite(_ROWS[i], HIGH);
  }
}

uint8_t HaxoNotes::getMidiNote() {
    uint32_t key = _scanKeys();
    
    // Yes, I know the linear search is O(N) and is terribly inefficient...
    // ... but it was the lazy first pass, and it seems to be quick enough!
    for (int i = 0; i < _NOTE_MAP_SIZE; i++) {
        if (_NOTE_MAP[i].key == key) {
            return _NOTE_MAP[i].note;
        }
    }
    return 0;
}

uint32_t HaxoNotes::_scanKeys() {
  uint32_t key_value = 0;
    for (int row = 0; row < _NUM_ROWS; row++) {
        digitalWrite(_ROWS[row], LOW);
        delayMicroseconds(10);
        for (int col = 0; col < _NUM_COLS; col++) {
            if (digitalRead(_COLS[col]) == LOW) {
                key_value |= (1 << (row * _NUM_COLS + col));
            }
        }
        digitalWrite(_ROWS[row], HIGH);
    }
    return key_value;
}
