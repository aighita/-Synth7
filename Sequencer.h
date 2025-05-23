
// File: Sequencer.h
#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <Arduino.h>
#include "Degree.h"

class Sequencer {
  public:
    Sequencer(uint8_t audioPin, uint8_t ledPin);
    void begin();
    void update();
    void toggle();

    void toggleBPM();
    void setBPM(int newBpm);

    void togglePatternLength();
    void setPatternLength(int newLength);

    void toggleMetronome();
    int  transpose(int freq);
    void toggleTransposeSemiTones();
    void toggleScaleMinor();
    int  transposeOctave(int freq);

    void addStep(Degree degree);
    void clear();

    void introSong() const;

    bool getMetronome() const;
    int  getTransposeOctave() const; 
    void setTransposeOctave(int value);
    int  getScaleMinor() const;
    int  getTransposeSemiTones() const;
    int  getStepLengthMs() const;
    int  getLastStepTime() const;
    int  getReadIndex() const;
    int  getBPM() const;
    int  getPatternLength() const;
    bool isPlaying() const;

  private:
    static const int MAX_STEPS = 64;

    // Frequency lookup for each degree
    static const int degreeFreqs[7];

    uint8_t       audioPin_;
    uint8_t       ledPin_;
    int           pattern_[MAX_STEPS];
    int           patternLength_;
    int           bpm_;
    int           stepLengthMs_;
    int           writeIndex_;
    int           readIndex_;
    int           transposeSemiTones_;
    int           transposeOctave_;
    bool          isPlaying_;
    bool          metronome_;
    bool          scaleMinor_; // minor or major
    unsigned long lastStepTime_;
};

#endif // SEQUENCER_H