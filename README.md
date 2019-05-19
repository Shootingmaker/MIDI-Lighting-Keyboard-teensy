# MIDI-Lighting-Keyboard-teensy

[Library needs]

MIDI
https://github.com/FortySevenEffects/arduino_midi_library

MIDIcontoroller
https://github.com/joshnishikawa/MIDIcontroller

Teensyduino
https://www.pjrc.com/teensy/teensyduino.html

[Setting] 

board Teensy3.5

tool -> USB Type -> TeensyMIDI 

CPU:120Mhz

Faster with LTO


[Edit some libraly]

"MIDI.h" with MIDIcontoroller with TeensyMIDI
Change it
[midi_Settings.h]  
-> static const unsigned SysExMaxSize = 50000;

-> static const bool UseRunningStatus = true;

MIDIcontoroller
Change it
 [MIDIbutton.h]   - >#include "Flicker.h  =>  #include "Flicker/Flicker.h"

[Memo]
How to Using USB MIDI
https://www.pjrc.com/teensy/td_midi.html

[to LED(APA102) Wireing]
 5V & GND
 MOSI is  11
 CLK  is  13
