/* -----------------------------------------------------------------------------
[MIDI Lighting Keyboard Project.]
Kotohiro Masdua. 2019/2/14
-----------------------------------------------------------------------------*/
/*
[Library needs]
Arduiono MIDI (5.0 later)
https://github.com/FortySevenEffects/arduino_midi_library

MIDIcontoroller
https://github.com/joshnishikawa/MIDIcontroller

Flicker(MIDIcontoroller needs.)
https://github.com/joshnishikawa/Flicker

Teensyduino (for 1.8.12 later)
https://www.pjrc.com/teensy/teensyduino.html

FastLED 3.3.3
https://github.com/FastLED/FastLED


 [Setting] 
 Board Teensy4.0
 tool -> USB Type -> TeensyMIDI 
 CPU:600Mhz
 Faster
 
[Wireing to LED(APA102/SK9822)]
 5V    Almost needs 1000mA with Capacitor 100uF is Better.
 GND   Wide line.
 MOSI is  11
 CLK  is  13


 [Memo]
 How to Using USB MIDI
 https://www.pjrc.com/teensy/td_midi.html

  "MIDIcontoroller"
 Change it(some enviroment...)
 [MIDIbutton.h]   - > #include "Flicker.h  =>  #include "Flicker/Flicker.h"

-----------------------------------------------------------------------------*/

#include "MIDIcontroller.h"
static  const  unsigned SysExMaxSize = 1000*478 ;  //1000*xxx K
static  const  bool UseRunningStatus = true ; 
int FastLEDSet_Ch[128];          // Map of Who(channel) use LED? 
int shift= -20;           // Shift note, if few LEDs. "1"octave=12LEDs.
int Reverse = 128 ;
int calc = 0;

// -----------------------------------------------------------------------------
#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 128
#define DATA_PIN 11
#define CLOCK_PIN 13
#define BRIGHTNESS 20

// Define the array of leds
CRGB leds[NUM_LEDS];

int delayval = 5; // delay for test

// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------
// LED Blink control. 

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  if (velocity == 0) {  // 　Note ON "Velocity = 0" is NOTE Off.
    leds[shift+Reverse-pitch] = CRGB::Black;
  } else {
    switch (channel) {  //  Select Ch       //　Blink velocity power!
      case 1:
        calc = shift+Reverse-pitch;
        calc = constrain(calc, 0, 88);
        leds[calc] = CRGB::Green;
        FastLEDSet_Ch[calc]=1;
        break;
      case 2:
        calc = shift+Reverse-pitch;
        calc = constrain(calc, 0, 88);
        leds[calc] = CRGB::Blue;
        FastLEDSet_Ch[calc]=2;
        break;
      case 3:
        calc = shift+Reverse-pitch;
        calc = constrain(calc, 0, 88);
        leds[calc] = CRGB::Red;
        FastLEDSet_Ch[calc]=3;
        break;
      case 4:
        calc = shift+Reverse-pitch;
        calc = constrain(calc, 0, 88);
        leds[calc] = CRGB::Yellow;
        FastLEDSet_Ch[calc]=4;
        break;
      case 5:
        calc = shift+Reverse-pitch;
        calc = constrain(calc, 0, 88);
        leds[calc] = CRGB::Orange;
        FastLEDSet_Ch[calc]=5;
        break;
      case 6:
        calc = shift+Reverse-pitch;
        calc = constrain(calc, 0, 88);
        leds[calc] = CRGB::Fuchsia;
        FastLEDSet_Ch[calc]=6;
        break;
      case 7:
        calc = shift+Reverse-pitch;
        calc = constrain(calc, 0, 88);
        leds[calc] = CRGB::DeepSkyBlue;
        FastLEDSet_Ch[calc]=7;
        break;
      case 8:
        calc = shift+Reverse-pitch;
        calc = constrain(calc, 0, 88);
        leds[calc] = CRGB::MistyRose;
        FastLEDSet_Ch[calc]=8;
        break; 
      case 9:
        calc = shift+Reverse-pitch;
        calc = constrain(calc, 0, 88);
        leds[calc] = CRGB::GreenYellow;
        FastLEDSet_Ch[calc]=9;
        break;
      case 10:
        calc = shift+Reverse-pitch;
        calc = constrain(calc, 0, 88);
        leds[calc] = CRGB::DarkBlue;
        FastLEDSet_Ch[calc]=10;
        break;
      case 11:
        calc = shift+Reverse-pitch;
        calc = constrain(calc, 0, 88);
        leds[calc] = CRGB::Cyan;
        FastLEDSet_Ch[calc]=11;
        break;
      case 12:
        calc = shift+Reverse-pitch;
        calc = constrain(calc, 0, 88);
        leds[calc] = CRGB::LightCoral;
        FastLEDSet_Ch[calc]=12;
        break;
      case 13:
        calc = shift+Reverse-pitch;
        calc = constrain(calc, 0, 88);
        leds[calc] = CRGB::Purple;
        FastLEDSet_Ch[calc]=13;
        break;
      case 14:
        calc = shift+Reverse-pitch;
        calc = constrain(calc, 0, 88);
        leds[calc] = CRGB::FireBrick;
        FastLEDSet_Ch[calc]=14;
        break;
      case 15:
        calc = shift+Reverse-pitch;
        calc = constrain(calc, 0, 88);
        leds[calc] = CRGB::DeepSkyBlue;
        FastLEDSet_Ch[calc]=15;
        break;
      case 16:
        calc = shift+Reverse-pitch;
        calc = constrain(calc, 0, 88);
        leds[calc] = CRGB::WhiteSmoke;
        FastLEDSet_Ch[calc]=16;
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
      calc = shift+Reverse-pitch;
      calc = constrain(calc, 0, 88);
      leds[calc]= CRGB::Black;
      FastLEDSet_Ch[calc]=0;
      FastLED.show();
      break;
  }
}

void handleControlChange(byte channel , byte number , byte value )
{

  switch (number) {
    case 120: for(int i=0;i<NUM_LEDS;i++){leds[i]= CRGB::Black;}  break;  // 120 is All sound Off      : All LED OFF
    case 121: for(int i=0;i<NUM_LEDS;i++){leds[i]= CRGB::Black;}  break;  // 121 Reset All controller  : All LED OFF
    case 123: for(int i=0;i<NUM_LEDS;i++){leds[i]= CRGB::Black;}  break;  // 123 All Note Off         : All LED OFF
   }
  
  FastLED.show();  
}


// -----------------------------------------------------------------------------

void setup()
{
 
    //LED test All On! after OFF
    // -----------------------------------------------------------------------------
    FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);// global brightness
    
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot] = CRGB::Red;
            FastLED.show();
            // clear this led for the next time around the loop
            delay(delayval); // Delay for a period of time (in milliseconds).
            }

    for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot] = CRGB::Green;
            FastLED.show();
            // clear this led for the next time around the loop
            delay(delayval); // Delay for a period of time (in milliseconds).
            }
               
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot] = CRGB::Blue;
            FastLED.show();
            // clear this led for the next time around the loop
            delay(delayval); // Delay for a period of time (in milliseconds).
            }
            
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot]= CRGB::Black;
            FastLED.show();
            // clear this led for the next time around the loop
            delay(delayval); // Delay for a period of time (in milliseconds).
            }


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
            

}


void loop()
{
    usbMIDI.read();    
}
