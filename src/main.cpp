// This based on Control Surface CCButton example: https://tttapa.github.io/Control-Surface-doc/Doxygen/d9/d2e/CCButton_8ino-example.html
// It will turn XIAO into USB-MIDI device on MIDI Channel 1
// Encoder invoke CC (191) on Control Note 16 with value 65 (clockwise) and value 1 (counter clockwise)
// Button invoke CC (191) on Control Note 16 with value 0 (pressed) and value 127 (released)
// More on https://github.com/Atarity/knob-88 .

#include <Arduino.h>
#include <Control_Surface.h>

// Knob-88 Seeeduino XIAO definition (see readme.md for wiring)
#define buttonPin 8
#define buttonGndPin 10
#define encoderAPin 3
#define encoderGndPin 4
#define encoderBPin 5
#define encoderSpeed 1                // Multiplier if the control isn't fast enough

// Knob-98 Seeeduino XIAO definition (see readme.md for wiring)
//#define buttonPin 10
//#define buttonGndPin 9
//#define encoderAPin 4
//#define encoderGndPin 3
//#define encoderBPin 2
//#define encoderSpeed 2                  // Multiplier if the control isn't fast enough

USBMIDI_Interface midi;                 // Instantiate a MIDI over USB interface

CCButton button {                       // Define pushbutton
    buttonPin,
    {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1},     // General Purpose Controller #1 on MIDI channel 1
};

CCRotaryEncoder enc {                   // Define encoder
  {encoderAPin, encoderBPin},
  MCU::V_POT_1,                         // MIDI address (CC number + optional channel)
  encoderSpeed,                         // Optional multiplier if the control isn't fast enough
};

void setup() {
    pinMode(buttonGndPin, OUTPUT);
    digitalWrite(buttonGndPin, LOW);    // Set button pin to GND

    pinMode(encoderGndPin, OUTPUT);
    digitalWrite(encoderGndPin, LOW);   // Set central encoder pin to GND
    RelativeCCSender::setMode(relativeCCmode::MACKIE_CONTROL_RELATIVE);
    Control_Surface.begin();            // Initialize Control Surface
}

void loop() {
    Control_Surface.loop();             // Update the Control Surface
}