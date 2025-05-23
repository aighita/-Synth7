// File: Joystick.h
#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "Sequencer.h"
#include <Arduino.h>

class Joystick {
  public:
    Joystick(uint8_t xPin, uint8_t yPin, Sequencer &seq);
    void begin();
    void update();
    int getX() const;
    int getY() const;

  private:
    Sequencer &sequencer_;

    uint8_t xPin_, yPin_;
    int xVal_, yVal_;
};

#endif // JOYSTICK_H