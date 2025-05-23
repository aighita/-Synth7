// File: Options.cpp
#include "Options.h"

const uint8_t Options::degreePins_[7] = {4, 5, 13, 14, 27, 32, 33};

Options::Options(Sequencer &seq, DisplayManager &dsp)
  : sequencer_(seq), display_(dsp) {}

void Options::begin() {
  pinMode(clearSeqButtonPin_, INPUT_PULLUP);
}

void Options::update() {
  bool clrState = digitalRead(clearSeqButtonPin_);
  unsigned long now = millis();

  pressed_ = (clrState == LOW);

  if (!pressed_) return;

  for (uint8_t i = 0; i < 7; ++i) {
    bool state = digitalRead(degreePins_[i]);

    if (state == LOW && lastState_[i] == HIGH) {
      switch (i + 1) {
        // Increase BPM += 5 : [60, 210]
        case 1: sequencer_.toggleBPM(); break;

        // Increase pattern length {16, 32, 64}
        case 2: sequencer_.togglePatternLength(); break;

        // Metronome ON/OFF
        case 3: sequencer_.toggleMetronome(); break;

        // Transpose Key
        case 4: sequencer_.toggleTransposeSemiTones(); break;

        // Minor / Major scales
        case 5: sequencer_.toggleScaleMinor(); break;

        // Clear sequencer and display clear animation
        case 6:
          sequencer_.clear();
          display_.clearSequencer();
          break;

        // START / STOP sequencer
        case 7: sequencer_.toggle(); break;
        default: break;
      }
    }

    lastState_[i] = state;
  }
}

bool Options::isPressed() const { return pressed_; }
