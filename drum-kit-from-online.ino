



//  *****************************************************************************************************************
//  *                                                                                                               *
//  *                                         SpikenzieLabs.com                                                     *
//  *                                                                                                               *
//  *                                           Drum Kit - Kit                                                      *
//  *                                                                                                               *
//  *                                                                                                               *
//  *****************************************************************************************************************
//
//  BY: MARK DEMERS Copywrite 20009
//  April. 2009
//  VERSION: 1.b
//  Modified by Sagar Mekanikoa
//
//  DESCRIPTION:
//  Arduino analog input used to sense piezo drum hits then sent serialy to processing.
//  
//  Required - Hardware:
//  1. Drum kit - kit (From SpikenzieLabs.com)
//  2. Arduino
//
//  Required - Software:
//  1. Serial MIDI converter
//  2. Garage Band, Ableton Live etc ...
//
// LEGAL:
// This code is provided as is. No guaranties or warranties are given in any form. It is your responsibilty to 
// determine this codes suitability for your application.




//*******************************************************************************************************************
// User settable variables         
//*******************************************************************************************************************
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

unsigned char PadNote[6] = {60,61,62,63,64,65};         // MIDI notes from 0 to 127 (Mid C = 60)

int PadCutOff[6] = {1,1,1,1,1,1};           // Minimum Analog value to cause a drum hit

int MaxPlayTime[6] = {40,40,40,40,40,40};               // Cycles before a 2nd hit is allowed

boolean VelocityFlag  = true;                           // Velocity ON (true) or OFF (false)

int MidiChannel = 1;                                //MIDI Channel, 1-16



//*******************************************************************************************************************
// Internal Use Variables         
//*******************************************************************************************************************

boolean activePad[6] = {0,0,0,0,0,0};                   // Array of flags of pad currently playing
int PinPlayTime[6] = {0,0,0,0,0,0};                     // Counter since pad started to play

unsigned char status;

int pin = 0;     
int hitavg = 0;

//*******************************************************************************************************************
// Setup         
//*******************************************************************************************************************

void setup() 
{
  MIDI.begin();
}

//*******************************************************************************************************************
// Main Program         
//*******************************************************************************************************************

void loop() 
{
  for(int pin=0; pin < 6; pin++)
  {
    hitavg = analogRead(pin);                              // read the input pin

    if((hitavg > PadCutOff[pin]))
    {
      if((activePad[pin] == false))
      {
        if(VelocityFlag == true)
        {
          hitavg = (hitavg / 8) -1 ;                                                 // Upper range
        }
        else
        {
          hitavg = 127;
        }

 
        PinPlayTime[pin] = 0;
        activePad[pin] = true;
        MIDI.sendNoteOn(PadNote[pin],hitavg,MidiChannel);                               // Sends note, velocity, midi channel
        MIDI.sendNoteOff(PadNote[pin],0,MidiChannel);                           // This sends a NoteOn and a NoteOff message right after        
      }                                                                              
      else
      {
        PinPlayTime[pin] = PinPlayTime[pin] + 1;
      }
    }
    else if((activePad[pin] == true))
    {
      PinPlayTime[pin] = PinPlayTime[pin] + 1;
      
      if(PinPlayTime[pin] > MaxPlayTime[pin])
      {
        activePad[pin] = false;
      }
    }
  } 
}



