#include <MIDI.h>
#include "FastLED.h"

#define NUM_LEDS 60 //change to no. of leds you have, or less if you like
#define DATA_PIN 7 //change to pin you are using for the signal output for the leds
CRGB leds[NUM_LEDS];// Define the array of leds

int kickTrigger = 0;
int snareTrigger = 0;
int tom1Trigger = 0;
int tom2Trigger = 0;

MIDI_CREATE_DEFAULT_INSTANCE();

// -----------------------------------------------------------------------------

// This function will be automatically called when a NoteOn is received.
// It must be a void-returning function with the correct parameters,

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  if (pitch == 36 && channel == 10) {
    kickTrigger = 200;
  }

  //Coul you Switch / Case here if you wanted to

  if (pitch == 37 && channel == 10) {
    snareTrigger = 200;
  }

  if (pitch == 40 && channel == 10) {
    tom1Trigger = 200;
  }

  if (pitch == 41 && channel == 10) {
    tom2Trigger = 200;
  }

}

// -----------------------------------------------------------------------------

void setup()
{
  //initialise fastLED to use appropriate LED type, number and pin as defined above
  FastLED.addLeds<WS2812, DATA_PIN>(leds, NUM_LEDS);

  // Connect the handleNoteOn function to the library,
  // so it is called upon reception of a NoteOn.
  MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function


  // Initiate MIDI communications, listen to all channels
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop()
{
  // Call MIDI.read the fastest you can for real-time performance.
  MIDI.read();

  if (kickTrigger > 0) {
    kickTrigger = kickTrigger - 5; //this is basically a '
    //decay rate' for the light brightness the way it is used
  }

  if (snareTrigger > 0) {
    snareTrigger = snareTrigger - 0.1; //this is basically a
    //'decay rate' for the light brightness the way it is used
  }

  if (tom1Trigger > 0) {
    tom1Trigger = tom1Trigger - 0.1; //this is basically a
    //'decay rate' for the light brightness the way it is used
  }

  if (tom2Trigger > 0) {
    tom2Trigger = tom2Trigger - 0.1; //this is basically a
    //'decay rate' for the light brightness the way it is used
  }

  simpleRedFade();//call function to do stuff to the leds
  equalPartsFade();
  FastLED.show(); //the part that actually sends the light data to the leds

  // There is no need to check if there are messages incoming
  // if they are bound to a Callback function.
  // The attached method will be called automatically
  // when the corresponding message has been received.



}


void equalPartsFade() {

  int segmentSize = NUM_LEDS / 4.0;

  //for (int i = 0; i < segmentSize; i++) {
  //  leds[i] = CRGB (kickTrigger, kickTrigger, kickTrigger);
 // }

  for (int i = segmentSize; i < segmentSize * 2; i++) {
    leds[i] = CRGB (snareTrigger, 0, 0);
  }

  for (int i = segmentSize * 2; i < segmentSize * 3; i++) {
    leds[i] = CRGB (0, 0, tom1Trigger/2);
  }

  for (int i = segmentSize * 3; i < NUM_LEDS; i++) {
    leds[i] = CRGB (tom2Trigger, 0, 0);
  }


}
void simpleRedFade() {
  //this makes it so each and every note received starts a fading red colour
  //which resets when there's a new note.
  //as an exercise then try to think how to make it so you can do different colours
  //or make it a different speed
  //or make it work based on times instead of frames (currently it will fade faster on a faster MCU)
  //or make it work so it looks like a digital VU meter instead of a fade.
  //iterate through all the leds
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(kickTrigger / 4, kickTrigger / 4, kickTrigger / 4); //set led to a red which is the brightness of the triggerValue
    //divided by 4 to put within range - needs to be 0-255
    //CRGB is the datatype used for leds - that part creates a new colour using CRGB(red,green,blue) where each is 0-255
    //you can also use CHSV(Hue,Saturation,Value) where keeping saturation at 0 and value at 255 and cycling hue makes a rainbow cycle
    //saturation is whiteness so changing that makes colours more or less pastel
    //look up 'HSV' or 'colour spaces' for more info but it's not essential to know more than RGB
  }

}



