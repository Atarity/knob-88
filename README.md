# Knob-88
Smallest USB-C encoder you can make in 8 min for $8. You can use MIDI or HID or whatever you want "X over USB" protocol. It is also Arduino compatible so you can use all your beloved fancy-shmancy libraries.

![KNOB-88](/pics/knob-88.jpg)

## Bill Of Materials
- $5 [Seeeduino XIAO](https://www.seeedstudio.com/Seeeduino-XIAO-Arduino-Microcontroller-SAMD21-Cortex-M0+-p-4426.html)
- $3 Rotary encoder with integrated button, 9-11mm footprint and vertical orientation. It is most common type on the market, actually.

I recommend Bourns [PEC11L series](https://www.bourns.com/products/encoders/contacting-encoders/product/PEC11L). I've used PEC11R-4015F0-S0024. Another popular brands is Alps, Alpha, Elma and tons of their chinese clones. Check datasheet before buying.

## "Wiring"
0 wires. There is only 5 soldering points. Remove all unnecessary mounting pins from encoder to avoid short circuit before soldering.

![KNOB-88 wiring](/pics/88-wiring.jpg)

## Firmware
Source  code in this repo made with [PlatformIO IDE](https://platformio.org/).
- Install [Control Surface](https://github.com/tttapa/Control-Surface) library from **master** like `pio lib install https://github.com/tttapa/Control-Surface.git#master`. It is essential to use latest version which is [well- documented](https://tttapa.github.io/Control-Surface-doc/Doxygen/d2/d1f/RotaryEncoder_8ino-example.html).
- Install [MIDIUSB](https://github.com/arduino-libraries/MIDIUSB) library with `pio lib install "arduino-libraries/MIDIUSB"`

You also could use Arduino IDE. Just install [Control Surface](https://github.com/tttapa/Control-Surface) and [MIDIUSB](https://github.com/arduino-libraries/MIDIUSB) libraries as well.

# Knob-98
Knob-98 is an alternative design which required additional 1 minute to build.

![KNOB-98](/pics/knob-98.jpg)

It used the back side of XIAO to mount encoder so you need to solder **1 additional jumper** to configure button properly. You only need to uncomment `Knob-98 definition` section in the `/src/main.cpp` and comment `Knob-88` back then build the firmware.

![KNOB-98 wiring](/pics/98-wiring.jpg)

Advantages against Knob-88:
- You could use SMT encoders cause back side of the XIAO has a perfectly flat surface.
- Encoder will be soldered into geometric center of the XIAO.