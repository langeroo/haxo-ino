# What is haxo-ino?
haxo-ino is an Arduino/C++ port of [haxo-rs](https://github.com/cardonabits/haxo-rs) by @cardonabits to run the [Haxophone](https://www.crowdsupply.com/cardona-bits/haxophone). It is narrower in scope than haxo-rs in that its only goal is send MIDI commands out over USB to a host device; there is no audio being sent to the Haxophone's 3.5mm headphone jack. Since the system runs on a microcontroller, the MIDI controller is ready ~2 seconds after being plugged in, rather than the ~2 minutes needed to start the system up the Pi Zero.

# What Do I Need?
- A [Waveshare RP2040-PiZero](https://www.waveshare.com/rp2040-pizero.htm) ([Amazon link](https://www.amazon.com/dp/B0CJ6VM6H6)), which is _nearly_ pin-to-pin compatible with the standard Raspberry Pi GPIO setup.
- USB Type C cable
- Arduino IDE
- A host device to play music through

# How To
- `git clone` this repo
- Open Arduino IDE and open the `haxo` Arduino package
- Install the following:
  - Boards Manager
    - Raspberry Pi Pico/RP2040 by Earle Philhower
  - Libraries
    - MIDI Library by Francois Best
    - Adafruit TinyUSB Library
- Plug in, select your device port, compile, and upload to board
