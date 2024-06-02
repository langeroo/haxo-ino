#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

#include "Velocity.h"
#include "HaxoNotes.h"

const int TRANSPOSE = -9; // Alto Sax Transpose is -9
const uint8_t VEL_THRESH = 10;
const bool DEBUG = true;

const int MIDI_CHANNEL = 1;
const int MIDI_CC_VOLUME = 7;

Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDIusb);
Velocity velocity = Velocity();
HaxoNotes haxoNotes = HaxoNotes();

uint8_t lastNote = 0;
int lastVel = 0;

void setup() {
    Serial.begin(115200);
    
    velocity.init();
    haxoNotes.init();
    
    MIDIusb.begin(MIDI_CHANNEL_OMNI);
    MIDIusb.turnThruOff();
}

void loop() {
  int vel = velocity.getVelocity();
  uint8_t midiNote = haxoNotes.getMidiNote();
  if (DEBUG) {
    Serial.print(vel); Serial.print("/"); Serial.println(midiNote);  
  }

  // Adjust MIDI velocity of last note
  if (lastVel != vel) {
    midiSetVolume(max(0,vel));
    lastVel = vel;
  }
  
  if (midiNote != 0) {
    if (vel > VEL_THRESH) {
      if (lastNote != midiNote) {
        midiNoteOff(lastNote);
        midiNoteOn(midiNote, vel);
        lastNote = midiNote;
      }
    } else if (lastNote != 0) {
      midiNoteOff(lastNote);
      lastNote = 0;
    }
  }
}

void midiSetVolume(int vel) {
  MIDIusb.sendControlChange(MIDI_CC_VOLUME, vel, MIDI_CHANNEL);
}

void midiNoteOn(uint8_t note, int vel) {
  midiSetVolume(vel);
  MIDIusb.sendNoteOn(note + TRANSPOSE, 127, MIDI_CHANNEL);
}

void midiNoteOff(uint8_t note) {
  midiSetVolume(0);
  MIDIusb.sendNoteOff(note + TRANSPOSE, 0, MIDI_CHANNEL);
}
