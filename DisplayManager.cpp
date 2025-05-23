// File: DisplayManager.cpp
#include "DisplayManager.h"

#include <cstring>

DisplayManager::DisplayManager(const Sequencer &seq)
  : sequencer_(seq), lcd_(0x27, 16, 2), lastUpdate_(0) {}

void DisplayManager::begin() {
  Wire.begin(21, 22);
  lcd_.init();
  lcd_.backlight();
  lcd_.clear();
  lcd_.setCursor(0, 0);

  for (int i = 0; i < 12; i++) {
    switch (i % 4) {
      case 0:
        // lcd_.clear();
        lcd_.setCursor(0, 0);
        lcd_.print("uSynth7 init    ");
        delay(250);
        break;
      case 1:
        // lcd_.clear();
        lcd_.setCursor(0, 0);
        lcd_.print("uSynth7 init .  ");
        delay(250);
        break;
      case 2:
        // lcd_.clear();
        lcd_.setCursor(0, 0);
        lcd_.print("uSynth7 init .. ");
        delay(250);
        break;
      case 3:
        // lcd_.clear();
        lcd_.setCursor(0, 0);
        lcd_.print("uSynth7 init ...");
        delay(250);
        break;
      default:
        // lcd_.clear();
        lcd_.setCursor(0, 0);
        lcd_.print("uSynth7 init ...");
    }
  }

  lcd_.clear();
}

void DisplayManager::clearSequencer(
    uint8_t  columns,
    char     fillChar,
    uint16_t typeDelayMs,
    uint16_t holdDelayMs,
    uint16_t eraseDelayMs,
    bool     eraseForward,
    const char* message,
    uint8_t  windowSize,
    uint16_t msgDelayMs
) {
    // build up underscores one-by-one
    lcd_.clear();
    lcd_.setCursor(0, 0);
    for (uint8_t i = 0; i < columns; ++i) {
        lcd_.print(fillChar);
        delay(typeDelayMs);
    }
    delay(holdDelayMs);

    lcd_.setCursor(0, 1);
    typeSlidingWindow(message, 0, 1, windowSize, msgDelayMs);
}

void DisplayManager::typeSlidingWindow(
    const char* text,
    uint8_t     x,
    uint8_t     y,
    uint8_t     windowSize,
    uint16_t    stepDelayMs
) {
    size_t len = std::strlen(text);
    for (size_t i = 0; i < len; ++i) {
        uint8_t writePos = x + i;

        // 1) print the new character at (x+i, y)
        lcd_.setCursor(writePos, y);
        lcd_.print(text[i]);

        // 2) once we've got windowSize chars on screen,
        //    clear the char windowSize behind
        if (i >= windowSize) {
            lcd_.setCursor(writePos - windowSize, y);
            lcd_.print(' ');
        }

        delay(stepDelayMs);
    }
}

void DisplayManager::update() {
  unsigned long now = millis();
  if (now - lastUpdate_ < sequencer_.getStepLengthMs()) return;

  lastUpdate_ = now;

  // First ROW
  lcd_.setCursor(0, 0);
  int bpm = sequencer_.getBPM();
  if (bpm < 100) lcd_.print(" ");
  lcd_.print(bpm); lcd_.print("BPM ");

  int readIdx = sequencer_.getReadIndex();
  if (readIdx < 10) lcd_.print(" ");
  lcd_.print(readIdx); lcd_.print("/"); lcd_.print(sequencer_.getPatternLength());
  if (sequencer_.isPlaying()) {
    const char* spinner[] = { "|", "/", "-", "o"};
    lcd_.print(" ");
    if (sequencer_.getMetronome()) {
      if (sequencer_.getReadIndex() % 4 == 0) lcd_.print("|");
      else lcd_.print(" ");
    } else lcd_.print("|");
    lcd_.print(" ");
    lcd_.print(spinner[readIdx % 4]);
  } else (lcd_.print(" | o"));
 
  // Second ROW
  lcd_.setCursor(0, 1);
  // lcd_.print("                ");
  const char* key[] = {"C  ", "C# ", "D  ", "Eb ", "E  ", "F  ", "Gb ", "G  ", "G# ", "A  ", "A# ", "B  "};
  lcd_.print(key[abs(12 + sequencer_.getTransposeSemiTones()) % 12]);
  sequencer_.getScaleMinor() ? lcd_.print("Min ") : lcd_.print("Maj ");

  // Transpose Info
  int semiTonesTransposeData = sequencer_.getTransposeSemiTones() + sequencer_.getTransposeOctave() * 12;
  Serial.print("T data: "); Serial.println(semiTonesTransposeData);
  lcd_.print("T");
  if (semiTonesTransposeData >= 0) {
    if (semiTonesTransposeData < 10) lcd_.print("   ");
    else lcd_.print("  ");
    lcd_.print(semiTonesTransposeData);
  } else {
    unsigned int absData = abs(semiTonesTransposeData);
    lcd_.print(" -");
    if (absData < 10) lcd_.print(" ");
    lcd_.print(absData);
  }

  lcd_.print(" ");
  if (sequencer_.getMetronome()) {
    if (sequencer_.getReadIndex() % 4 == 0) lcd_.print("|");
    else lcd_.print(" ");
  } else lcd_.print("|");
  lcd_.print(" ");

  //TODO: Change this to signal if using PWM or DAC pin for freq
  lcd_.print("?");
}
