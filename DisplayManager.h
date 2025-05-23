// File: DisplayManager.h
#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H
#include <Arduino.h>
#include <Wire.h>
#include "Degree.h"  // ensure compatible with ESP32
#include <LiquidCrystal_I2C.h> // make sure to install an ESP32-compatible variant
#include "Sequencer.h"
#include "Options.h"

class DisplayManager {
  public:
    explicit DisplayManager(const Sequencer &seq);
    void begin();
    void update();

    void clearSequencer(
      uint8_t  columns       = 16,      // width of the sequencer row
      char     fillChar      = '_',     // char to build the line
      uint16_t typeDelayMs   = 25,      // ms between each underscore
      uint16_t holdDelayMs   = 300,     // ms to pause on full line
      uint16_t eraseDelayMs  = 50,      // ms between each underscore-erase
      bool     eraseForward  = true,    // direction of the underscore-wipe
      const char* message    = "Cleared Sequence", // text to type afterward
      uint8_t  windowSize    = 3,       // sliding window length
      uint16_t msgDelayMs    = 50      // ms between each character of message
  );

  private:
    const Sequencer &sequencer_;
    LiquidCrystal_I2C lcd_;
    unsigned long lastUpdate_;
    void typeSlidingWindow(
      const char* text,
      uint8_t     x,
      uint8_t     y,
      uint8_t     windowSize,
      uint16_t    stepDelayMs
  );
};
#endif // DISPLAYMANAGER_H
