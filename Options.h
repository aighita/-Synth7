// File: Options.h
#ifndef OPTIONS_H
#define OPTIONS_H

#include <Arduino.h>
#include "Sequencer.h"
#include "DisplayManager.h"

class DisplayManager;

class Options {
  public:
    explicit Options(Sequencer &seq, DisplayManager &dsp);
    void begin();
    void update();
    bool isPressed() const;

  private:
    Sequencer &sequencer_;
    DisplayManager &display_;
    static constexpr uint8_t clearSeqButtonPin_    = 19;
    bool pressed_;
    static const uint8_t degreePins_[7];
    bool lastState_[7];
};

#endif // OPTIONS_H
