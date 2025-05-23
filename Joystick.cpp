// File: Joystick.cpp
#include "Joystick.h"

Joystick::Joystick(uint8_t xPin, uint8_t yPin, Sequencer &seq)
  : xPin_(xPin), yPin_(yPin), xVal_(0), yVal_(0), sequencer_(seq)
{}

void Joystick::begin() {}

void Joystick::update() {
  xVal_ = analogRead(xPin_);
  yVal_ = analogRead(yPin_);

  if (yVal_ == 0) sequencer_.setTransposeOctave(1);
  else if (yVal_ == 4095) sequencer_.setTransposeOctave(-1);
  else sequencer_.setTransposeOctave(0);
}

int Joystick::getX() const { return xVal_; }
int Joystick::getY() const { return yVal_; }