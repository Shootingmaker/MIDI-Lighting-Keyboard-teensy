/* -----------------------------------------------------------------------------
[MIDI Lighting Keyboard Project.]
Kotohiro Masdua. 2019/2/14
-----------------------------------------------------------------------------*/
/*
[Library needs]
 Arduiono MIDI
https://github.com/FortySevenEffects/arduino_midi_library
MIDIcontoroller
https://github.com/joshnishikawa/MIDIcontroller
Teensyduino
https://www.pjrc.com/teensy/teensyduino.html

 [Setting] 
 Board Teensy3.5
 tool -> USB Type -> TeensyMIDI 
 CPU:120Mhz
 Faster with LTO

//[Edit some libraly]
 first understand.
 "MIDI.h" with MIDIcontoroller with TeensyMIDI

 Change it
 
 "midi_Settings.h" 
 -> static const unsigned SysExMaxSize = 50000;
 -> static const bool UseRunningStatus = true;

 "MIDIcontoroller"
 Change it
 [MIDIbutton.h]   - > #include "Flicker.h  =>  #include "Flicker/Flicker.h"

 [Memo]
 How to Using USB MIDI
 https://www.pjrc.com/teensy/td_midi.html

[Wireing to LED(APA102)]
 5V    Almost needs 1000mA with Capacitor 100uF is Better.
 GND   Wide line.
 MOSI is  11
 CLK  is  13

-----------------------------------------------------------------------------*/

#include "MIDIcontroller.h"

int FastLEDSet_Ch[128];          // Map of Who(channel) use LED? 

// -----------------------------------------------------------------------------
#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 128
#define DATA_PIN 11
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

int delayval = 2; // delay for test

// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------
// LED Blink control. 

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  if (velocity == 0) {  // 　Note ON "Velocity = 0" is NOTE Off.
    leds[pitch].setRGB( 0, 0, 0);
  } else {
    switch (channel) {  //  Select Ch       //　Blink velocity power!
      case 1:
        leds[pitch] = 0x008000;
        FastLEDSet_Ch[pitch]=1;
        break;
      case 2:
        leds[pitch] = 0x0000FF;
        FastLEDSet_Ch[pitch]=2;
        break;
      case 3:
        leds[pitch] = 0xFF0000;
        FastLEDSet_Ch[pitch]=3;
        break;
      case 4:
        leds[pitch] = 0xFFFF00;
        FastLEDSet_Ch[pitch]=4;
        break;
      case 5:
        leds[pitch] = 0xFFA500;
        FastLEDSet_Ch[pitch]=5;
        break;
      case 6:
        leds[pitch] = 0xFF00FF;
        FastLEDSet_Ch[pitch]=6;
        break;
      case 7:
        leds[pitch] = 0x00BFFF;
        FastLEDSet_Ch[pitch]=7;
        break;
      case 8:
        leds[pitch] = 0xFFE4E1;
        FastLEDSet_Ch[pitch]=8;
        break; 
      case 9:
        leds[pitch] = 0xADFF2F;
        FastLEDSet_Ch[pitch]=9;
        break;
      case 10:
        leds[pitch] = 0x00008B;
        FastLEDSet_Ch[pitch]=10;
        break;
      case 11:
        leds[pitch] = 0x00FFFF;
        FastLEDSet_Ch[pitch]=11;
        break;
      case 12:
        leds[pitch] = 0xF08080;
        FastLEDSet_Ch[pitch]=12;
        break;
      case 13:
        leds[pitch] = 0x800080;
        FastLEDSet_Ch[pitch]=13;
        break;
      case 14:
        leds[pitch] = 0xB22222;
        FastLEDSet_Ch[pitch]=14;
        break;
      case 15:
        leds[pitch] = 0x00BFFF;
        FastLEDSet_Ch[pitch]=15;
        break;
      case 16:
        leds[pitch] = 0xF5F5F5;
        FastLEDSet_Ch[pitch]=16;
        break;        
    }

  }
      FastLED.show();
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  switch (channel) {
    case 1: 
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
      leds[pitch].setRGB( 0, 0, 0); FastLEDSet_Ch[pitch]=0;
      FastLED.show();
      break;
  }
}

void handleControlChange(byte channel , byte number , byte value )
{

  switch (number) {
    case 120: for(int i=0;i<NUM_LEDS;i++){leds[i].setRGB( 0, 0, 0);}  break;  // 120 is All sound Off      : All LED OFF
    case 121: for(int i=0;i<NUM_LEDS;i++){leds[i].setRGB( 0, 0, 0);}  break;  // 121 Reset All controller  : All LED OFF
    case 123: for(int i=0;i<NUM_LEDS;i++){leds[i].setRGB( 0, 0, 0);}  break;  // 123 All Note Off         : All LED OFF
   }
  
  FastLED.show();  
}


// -----------------------------------------------------------------------------

void setup()
{

    // -----------------------------------------------------------------------------
    // UsehandleNoteOn Handler with MIDI Library ,after NoteOn Call Back Handler
    usbMIDI.setHandleNoteOn(handleNoteOn);  //argument is Handler [function].

    // Use NoteOff Handler
    usbMIDI.setHandleNoteOff(handleNoteOff);

    // Use ControlChange Handler
    usbMIDI.setHandleControlChange(handleControlChange);

    // All Ch read with MIDI instance initialize.
    usbMIDI.begin();
    // -----------------------------------------------------------------------------

    
    //LED test All On! after OFF
    // -----------------------------------------------------------------------------
    FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot].setRGB( 20, 0, 0);
            FastLED.show();
            // clear this led for the next time around the loop
            delay(delayval); // Delay for a period of time (in milliseconds).
            }

    for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot].setRGB( 0, 20, 0);
            FastLED.show();
            // clear this led for the next time around the loop
            delay(delayval); // Delay for a period of time (in milliseconds).
            }
               
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot].setRGB( 0, 0, 20);
            FastLED.show();
            // clear this led for the next time around the loop
            delay(delayval); // Delay for a period of time (in milliseconds).
            }
            
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot].setRGB( 0, 0, 0);
            FastLED.show();
            // clear this led for the next time around the loop
            delay(delayval); // Delay for a period of time (in milliseconds).
            }

}


void loop()
{
    usbMIDI.read();    
}
