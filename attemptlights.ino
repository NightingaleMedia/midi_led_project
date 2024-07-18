#include <MIDI.h>
#include <FastLED.h>
#define NUM_LEDS 10
#define LED 13  //Debug LED

#define DATA_PIN 7      // Green
#define CLOCK_PIN 6     // Blue
CRGB leds[NUM_LEDS];

int ledPin = 13;

void OnNoteOn(byte channel, byte note, byte velocity)
{
  lightsOn();
  digitalWrite(ledPin, HIGH);
}

void OnNoteOff(byte channel, byte note, byte velocity)
{
  digitalWrite(ledPin, LOW);
  lightsOn();  
}

void setup()
{
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);
  FastLED.show();
  pinMode(ledPin, OUTPUT);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}

void loop()
{
  usbMIDI.read();
}

// function fading lights on
void lightsOn() {
  int lightsOnMaxBrightness = 64;
  int lightsOnMinBrightness = 2;

  for (int i = lightsOnMinBrightness; i < lightsOnMaxBrightness; i++) {
    lightsOnMinBrightness = i;
    FastLED.show();
    for ( int j = 0; j < NUM_LEDS; j++) {
      leds[j] = CRGB(lightsOnMinBrightness);
    }
  }
}

void lightsOff() {
  int lightsOffMaxBrightness = 64;
  int lightsOffMinBrightness = 2;

  for (int i = lightsOffMaxBrightness; i > lightsOffMinBrightness; i--) {
    lightsOffMaxBrightness = i;
    FastLED.show();
    for ( int j = 0; j < NUM_LEDS; j++) {
      leds[j] = CRGB(lightsOffMaxBrightness);
    }
  }
}

