// File: uSynth7.ino
#include <Arduino.h>
#include <ESP32Servo.h>

#include "Sequencer.h"
#include "Buttons.h"
#include "Joystick.h"
#include "Options.h"
#include "DisplayManager.h"

volatile float currentFreq = 0;

const int dacPin1_Left = 25;    // DAC1 - pentru PAM8403
const int dacPin2_Right = 26;   // DAC2 - pentru PAM8403
const int pwmPin = 18;          // PWM - pentru buzzer

Sequencer      sequencer(pwmPin, dacPin1_Left, dacPin2_Right, 2);
DisplayManager display(sequencer);
Options        options(sequencer, display);
Buttons        buttons(sequencer, options);
Joystick       joystick(34, 35, sequencer);

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  options.begin();
  buttons.begin();
  joystick.begin();
  display.begin();
  sequencer.begin();
}

void loop() {
  options.update();
  buttons.update();
  joystick.update();
  sequencer.update();
  display.update();
}
