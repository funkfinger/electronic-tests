// Adafruit Circuit Playground speaker library
// by Phil Burgess / Paint Your Dragon.

#ifndef ADAFRUIT_CPLAY_SPEAKER_H
#define ADAFRUIT_CPLAY_SPEAKER_H

class Adafruit_CPlay_Speaker {
 public:
  Adafruit_CPlay_Speaker(void) {}; // Empty constructor
  void begin(void),
       end(void),
       set(uint8_t value),
       playSound(const uint8_t *data, uint16_t length, uint16_t sampleRate);
 private:
  boolean started = false;
};

#endif // ADAFRUIT_CPLAY_SPEAKER_H
