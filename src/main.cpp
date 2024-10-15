// Include the required librariess
#include "Arduino.h"
#include <RotaryEncoder.h>
#include <elapsedMillis.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "TeensyThreads.h"
#include <RBD_Timer.h>
#include <RBD_Button.h>
#include "parameters.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform ModFreq;           // xy=179,108
AudioSynthWaveformModulated MainFreq; // xy=319,163
AudioEffectEnvelope envelope1;        // xy=447,223
AudioEffectDelay delay1;              // xy=563,341
AudioEffectDelay delay2;              // xy=720,403
AudioMixer4 mixer1;                   // xy=817,255
AudioMixer4 mixer2;                   // xy=948,342
AudioOutputI2S i2s1;                  // xy=1151,342
AudioConnection patchCord1(ModFreq, 0, MainFreq, 0);
AudioConnection patchCord2(MainFreq, envelope1);
AudioConnection patchCord3(envelope1, 0, mixer1, 0);
AudioConnection patchCord4(envelope1, delay1);
AudioConnection patchCord5(delay1, 0, mixer1, 1);
AudioConnection patchCord6(delay1, 1, mixer1, 2);
AudioConnection patchCord7(delay1, 1, delay2, 0);
AudioConnection patchCord8(delay2, 0, mixer1, 3);
AudioConnection patchCord9(delay2, 1, mixer2, 1);
AudioConnection patchCord10(mixer1, 0, mixer2, 0);
AudioConnection patchCord11(mixer2, 0, i2s1, 0);
AudioConnection patchCord12(mixer2, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1; // xy=551,611
// GUItool: end automatically generated code

// IO objects
RotaryEncoder encoderMainFreq(33, 34, RotaryEncoder::LatchMode::TWO03);
RotaryEncoder encoderLfoFreq(35, 36, RotaryEncoder::LatchMode::TWO03);
RotaryEncoder encoderLfoAmplitude(37, 38, RotaryEncoder::LatchMode::TWO03);
RotaryEncoder encoderDelayTime(28, 27, RotaryEncoder::LatchMode::TWO03);
RotaryEncoder encoderDelayFeedback(30, 29, RotaryEncoder::LatchMode::TWO03);
RotaryEncoder encoderLfoWaveform(31, 32, RotaryEncoder::LatchMode::FOUR3);
RotaryEncoder encoders[6] = {encoderMainFreq, encoderLfoFreq, encoderLfoAmplitude, encoderDelayTime, encoderDelayFeedback, encoderLfoWaveform};

// Variables to remember positions of encoders
int encoderMainFreqPosition = 0;
int encoderLfoFreqPosition = 0;
int encoderLfoAmplitudePosition = 0;
int encoderDelayTimePosition = 0;
int encoderDelayFeedbackPosition = 0;
int encoderLfoWaveformPosition = 0;
int encoderPositions[6] = {encoderMainFreqPosition,
                           encoderLfoFreqPosition,
                           encoderLfoAmplitudePosition,
                           encoderDelayTimePosition,
                           encoderDelayFeedbackPosition,
                           encoderLfoWaveformPosition};

// Button object
RBD::Button playSound(41, true);

// Synthetization parameters of the dub siren sound
// The objects used here are in parameters.h
// The String name parameter in these is a leftover from when this was supposed to have a display
parameter paramMainFreq("Main Frequency", 20.0f, 10000.0f);
parameter paramLfoFreq("LFO Frequency", 0.01f, 20.0f);
parameter paramLfoAmplitude("LFO Amplitude", 0.0f, 0.6f);
parameter paramDelayTime("Delay Time", 0.05f, 1000.0f);
parameter paramDelayFeedback("Delay Feedback", 0.0f, 1.0f);

void updateParam(int paramIndex, bool increment)
{
  switch (paramIndex)
  {
  // Main freq.
  case 0:
    paramMainFreq.update(increment);
    MainFreq.frequency(paramMainFreq.getValue());
  case 1:
    paramLfoFreq.update(increment);
    ModFreq.frequency(paramLfoFreq.getValue());
    break;
  case 2:
    paramLfoAmplitude.update(!increment);
    ModFreq.amplitude(paramLfoAmplitude.getValue());
    break;
  case 3:
    paramDelayTime.update(increment);
    delay1.delay(0, paramDelayTime.getValue());
    delay1.delay(1, paramDelayTime.getValue() * 2.0f);
    delay2.delay(0, paramDelayTime.getValue());
    delay2.delay(1, paramDelayTime.getValue() * 2.0f);
    break;
  case 4:
    paramDelayFeedback.update(increment);
    mixer1.gain(1, 0.25f * paramDelayFeedback.getValue());
    mixer1.gain(2, 0.15f * paramDelayFeedback.getValue());
    mixer1.gain(3, 0.09f * paramDelayFeedback.getValue());
    mixer2.gain(1, 0.03f * paramDelayFeedback.getValue());
    break;
  case 5:
    break;
  // This shouldn't happen I guess
  default:
    break;
  }
}

void pollEncoders()
{
  // Let's go through all the encoders
  for (int i = 0; i < 6; i++)
  {
    encoders[i].tick(); // Required to read new position
    int newPos = encoders[i].getPosition();
    // Are we in a new position?
    if (newPos != encoderPositions[i])
    {
      // Remember the position
      encoderPositions[i] = newPos;

      // Check if we're incrementing or decrementing
      bool increment = false;
      if ((int)encoders[i].getDirection() == 1)
      {
        increment = true;
      }

      // Now, update the parameter depending on the index
      updateParam(i, increment);
    }
  }
}

void setup()
{
  // Init audio
  AudioMemory(1200);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  // Init waveforms
  // The main (carrier) signal is volume 1, the frequency is determined by the parameter
  // Waveform is sine for now
  MainFreq.begin(1, paramMainFreq.getValue(), WAVEFORM_SQUARE);
  // The mod signal's volume and frequency are determined by the parameters
  // Waveform is square for now
  ModFreq.begin(paramLfoAmplitude.getValue(), paramLfoFreq.getValue(), WAVEFORM_SQUARE);

  // Init delay
  delay1.delay(0, paramDelayTime.getValue());
  delay1.delay(1, paramDelayTime.getValue() * 2.0f);
  delay1.disable(2); // Disable to save memory
  delay1.disable(3);
  delay1.disable(4);
  delay1.disable(5);
  delay1.disable(6);
  delay1.disable(7);
  // This is another delay connected in series
  delay2.delay(0, paramDelayTime.getValue());
  delay2.delay(1, paramDelayTime.getValue() * 2.0f);
  delay2.disable(2);
  delay2.disable(3);
  delay2.disable(4);
  delay2.disable(5);
  delay2.disable(6);
  delay2.disable(7);
  // Init mixers
  mixer1.gain(0, 0.5f);
  mixer1.gain(1, 0.25f * paramDelayFeedback.getValue());
  mixer1.gain(2, 0.15f * paramDelayFeedback.getValue());
  mixer1.gain(3, 0.09f * paramDelayFeedback.getValue());
  mixer2.gain(0, 1.0f); // Output from mixer 1
  mixer2.gain(1, 0.03f * paramDelayFeedback.getValue());

  // Define a simple envelope with 1ms attack and release
  envelope1.attack(5.0f);
  envelope1.sustain(5.0f);
  envelope1.release(5.0f);

  Serial.begin(115200);
}

void loop()
{
  if (playSound.onPressed())
  {
    envelope1.noteOn();
  }
  if (playSound.onReleased())
  {
    envelope1.noteOff();
  }
  pollEncoders();
}
