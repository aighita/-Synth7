// File: Buttons.cpp
#include "Buttons.h"
#include "Sequencer.h"

// Define static array
const uint8_t Buttons::degreePins_[7] = {4, 5, 13, 14, 27, 32, 33};

Buttons::Buttons(Sequencer &seq, Options &opts)
  : sequencer_(seq), options_(opts)
{
  for (int i = 0; i < 7; ++i) lastState_[i] = HIGH;
}

void Buttons::begin() {
  for (auto pin : degreePins_) pinMode(pin, INPUT_PULLUP);
}

void Buttons::update() {
  if (options_.isPressed()) return;  // Skip processing if Options is held

  for (uint8_t i = 0; i < 7; ++i) {
    bool state = digitalRead(degreePins_[i]);

    if (state == LOW && lastState_[i] == HIGH) {
      sequencer_.addStep(static_cast<Degree>(i));
    }
    lastState_[i] = state;
  }
}
