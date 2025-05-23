// File: Sequencer.cpp
#include "Sequencer.h"
#include <Arduino.h>

// C Minor Base
const int Sequencer::degreeFreqs[7] = {
  262, // I  – C4
  294, // II – D4
  311, // III – Eb4
  349, // IV – F4
  392, // V – G4
  415, // VI – Ab4
  466  // VII – Bb4
};

Sequencer::Sequencer(uint8_t audioPin, uint8_t ledPin)
  : audioPin_(audioPin)
  , ledPin_(ledPin)
  , patternLength_(16)
  , bpm_(130)
  , writeIndex_(0)
  , readIndex_(0)
  , transposeSemiTones_(0)
  , transposeOctave_(0)
  , isPlaying_(true)
  , metronome_(false)
  , scaleMinor_(true)
  , lastStepTime_(0)
{
  stepLengthMs_ = 60000 / bpm_ / 4;
  for (int i = 0; i < MAX_STEPS; ++i) pattern_[i] = 0;
}

int Sequencer::transposeOctave(int freq) {
  return round(freq * pow(pow(2.0, 1.0 / 12.0), 12 * transposeOctave_));
}

void Sequencer::introSong() const {
  const int pulses          = 16;     // how many steps in each phase
  const int minInterval     = 50;     // fastest on+off total (ms)
  const int maxInterval     = 300;    // slowest on+off total (ms)
  const int toneFreq        = degreeFreqs[0]; // C4 beep
  const uint8_t ledPin      = ledPin_;        // flash this LED
  const uint8_t audioPin    = audioPin_;      // send tone here

  // 2) Decelerate: fast→slow
  for (int i = 0; i <= pulses; ++i) {
    int interval = minInterval + ( (maxInterval - minInterval) * i / pulses );
    int onDur    = interval >> 1;
    tone(audioPin, toneFreq, onDur);
    digitalWrite(ledPin, HIGH);
    delay(onDur);
    noTone(audioPin);
    digitalWrite(ledPin, LOW);
    delay(interval - onDur);
  }

  // ensure everything’s off
  noTone(audioPin);
  digitalWrite(ledPin, LOW);
}

void Sequencer::begin() {
  pinMode(audioPin_, OUTPUT);
  pinMode(ledPin_, OUTPUT);
}

void Sequencer::toggleMetronome() {
  metronome_ = !metronome_;
}

void Sequencer::toggle() {
  isPlaying_ = !isPlaying_;
  if (!isPlaying_) {
    noTone(audioPin_);
    digitalWrite(ledPin_, LOW);
  }
  readIndex_ = 0;
  writeIndex_ = 0;
}

void Sequencer::clear() {
  for (int i = 0; i < MAX_STEPS; i++) pattern_[i] = 0;
}

void Sequencer::setBPM(int newBpm) {
  bpm_ = constrain(newBpm, 30, 300);
  stepLengthMs_ = 60000 / bpm_ / 4;
}

void Sequencer::toggleBPM() {
  switch (bpm_) {
    case 210: bpm_ = 60; break;
    default: bpm_ += 5; break;
  }
  stepLengthMs_ = 60000 / bpm_ / 4;
}

void Sequencer::togglePatternLength() {
  switch (patternLength_) {
    case 16: patternLength_ = 32; break;
    case 32: patternLength_ = 64; break;
    default: patternLength_ = 16; break;
  }
}

void Sequencer::toggleTransposeSemiTones() {
  transposeSemiTones_ = (transposeSemiTones_ + 1) % 12;
}

void Sequencer::toggleScaleMinor() {
  scaleMinor_ = !scaleMinor_;
}

void Sequencer::setPatternLength(int newLength) {
  if (newLength > 0 && newLength <= MAX_STEPS) {
    patternLength_ = newLength;
    writeIndex_ %= patternLength_;
    readIndex_  %= patternLength_;
  }
}

void Sequencer::addStep(Degree degree) {
  pattern_[writeIndex_] = degreeFreqs[static_cast<uint8_t>(degree)];
  writeIndex_ = (writeIndex_ + 1) % patternLength_;
}

int Sequencer::transpose(int freq) {
  // float ratio = pow(2.0, 1.0 / 12.0);
  return round(freq * pow(pow(2.0, 1.0 / 12.0), transposeSemiTones_));
}

void Sequencer::update() {
  if (!isPlaying_) return;
  unsigned long now = millis();
  if (now - lastStepTime_ < (unsigned long)stepLengthMs_) return;
  lastStepTime_ = now;
  // Serial.println("Updating sequencer.");

  if (metronome_) {
    if (readIndex_ % 16 == 0) tone(audioPin_, 800, 50);
    else if (readIndex_ % 4 == 0) tone(audioPin_, 1000, 50);
  }

  int freq = pattern_[readIndex_];
  if (freq > 0) {
    // tone(audioPin_, transpose(transposeOctave(freq)), stepLengthMs_);
    tone(audioPin_, transpose(transposeOctave(freq)));
    digitalWrite(ledPin_, HIGH);
  } else {
    noTone(audioPin_);
    digitalWrite(ledPin_, LOW);
  }

  readIndex_ = (readIndex_ + 1) % patternLength_;
  writeIndex_ = readIndex_;
}

// stepLengthMs_
bool Sequencer::getMetronome() const { return metronome_; }
int  Sequencer::getTransposeOctave() const { return transposeOctave_; } 
void Sequencer::setTransposeOctave(int value) { transposeOctave_ = value; }
int Sequencer::getScaleMinor() const { return scaleMinor_; }
int Sequencer::getTransposeSemiTones() const { return transposeSemiTones_; }
int Sequencer::getStepLengthMs() const { return stepLengthMs_; }
int Sequencer::getLastStepTime() const { return lastStepTime_; }
int Sequencer::getReadIndex() const { return readIndex_; }
int Sequencer::getBPM() const { return bpm_; }
int Sequencer::getPatternLength() const { return patternLength_; }
bool Sequencer::isPlaying() const { return isPlaying_; }