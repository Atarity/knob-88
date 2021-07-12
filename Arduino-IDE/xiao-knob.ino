// MIDIUSB and Control-Surface libs should be installed

#include <Control_Surface.h>

USBMIDI_Interface midi; // Instantiate a MIDI over USB interface

// Instantiate a CCButton object
CCButton button {
    // Push button on pin 8:
    8,
    // General Purpose Controller #1 on MIDI channel 1:
    {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1},
};

CCRotaryEncoder enc {
  {3, 5},       // pins
  MCU::V_POT_1, // MIDI address (CC number + optional channel)
  1,            // optional multiplier if the control isn't fast enough
};

void setup() {
    pinMode(10, OUTPUT);
    digitalWrite(10, LOW);   // setting pin to GND

    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);

    RelativeCCSender::setMode(relativeCCmode::MACKIE_CONTROL_RELATIVE);
    Control_Surface.begin(); // Initialize Control Surface
}

void loop() {
    Control_Surface.loop(); // Update the Control Surface
}
