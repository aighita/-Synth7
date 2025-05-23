// File: Buttons.h
#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include "Degree.h"
#include "Options.h"

class Sequencer; // forward declare
// class Options;

class Buttons {
  public:
    explicit Buttons(Sequencer &seq, Options &opts);
    void begin();
    void update();

  private:
    Sequencer &sequencer_;
    Options &options_;
    static const uint8_t degreePins_[7];
    bool lastState_[7];
};

#endif // BUTTONS_H