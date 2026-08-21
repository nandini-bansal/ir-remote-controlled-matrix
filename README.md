# IR-Controlled LED Matrix Patterns

An Arduino project where an IR remote control sends signals that are decoded and 
translated into different lighting patterns on an 8x8 LED matrix.

## How it works
- An IR receiver picks up signals from a remote control.
- The Arduino decodes the button press and maps it to a specific pattern.
- The 8x8 LED matrix displays that pattern — currently supports a smiley face, 
  a heart, the letter N, single row and the full matrix light up.

## Components used
- Arduino Uno
- IR Receiver Module VS1838B + Remote
- 8x8 LED Matrix (with MAX7219 driver)
- Jumper wires, breadboard

## Code
See `ir_sensor.ino` for the full sketch. Each pattern is stored as an 8-byte 
array representing the matrix rows — add new patterns by defining a new array and 
mapping it to a remote button code.

## Demo
Please check out this linkedin post of mine to see this project in action
[Click here!](https://www.linkedin.com/feed/update/urn:li:activity:7493626347496579072/)
