#include <MIDI.h>
#include "FastLED.h"
#define NUM_LEDS 10
#define DATA_PIN 7
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];

MIDI_CREATE_DEFAULT_INSTANCE();

// -----------------------------------------------------------------------------

// This function will be automatically called when a NoteOn is received.
// It must be a void-returning function with the correct parameters,
// see documentation here:
// http://arduinomidilib.fortyseveneffects.com/a00022.html

void handleNoteOn(byte channel, byte note , byte velocity )
{
    // Do whatever you want when a note is pressed.
   leds[NUM_LEDS] = CRGB::Red;
          FastLED.show();
    // Try to keep your callbacks short (no delays ect)
    // otherwise it would slow down the loop() and have a bad impact
    // on real-time performance.
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
    // Do something when the note is released.
    // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
      leds[NUM_LEDS] = CRGB::Black;
          FastLED.show();
}

// -----------------------------------------------------------------------------

void setup()
{
    // Connect the handleNoteOn function to the library,
    // so it is called upon reception of a NoteOn.
    MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function

    // Do the same for NoteOffs
    MIDI.setHandleNoteOff(handleNoteOff);

    // Initiate MIDI communications, listen to all channels
    MIDI.begin(MIDI_CHANNEL_OMNI);
    
    FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);

}

void loop()
{
    // Call MIDI.read the fastest you can for real-time performance.
    MIDI.read();
  FastLED.show();
    // There is no need to check if there are messages incoming
    // if they are bound to a Callback function.
    // The attached method will be called automatically
    // when the corresponding message has been received.
}
