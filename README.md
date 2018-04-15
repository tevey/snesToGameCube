# SNES to GameCube adapter

Code for building a SNES to GameCube adapter.

## Software Requirements
- [Arduino IDE (tested on 1.8.1)](https://www.arduino.cc/en/Main/Software)
- [Arduino Nintendo Library](https://github.com/NicoHood/Nintendo) by NicoHood

## Hardware

### Parts
- Logic Level Converter 5v <-> 3.3v
- Arduino Pro Mini (5v 16MHz)
- 1kΩ Resistor
- Female SNES controller port
- Male GameCube controller connector

### Wiring
![Wiring diagram](https://github.com/tevey/snesToGameCube/blob/master/snesToGameCube_bb.png)

The colors of the wires in the cables may not match between the original controller and the extension cable, below is the mapping for my cables the colors may be different for you.

#### SNES pinout
Type	| Original Controller  | Extension Cable
--------|-----------|----------------
5v		| white 	| green
clock	| yellow 	| yellow
latch	| orange 	| white
data	| red 		| red
gnd		| brown 	| black

#### GameCube Pinout
Type	| Original Controller 	| Extension Cable
--------|-----------|----------------
gnd		| Black 	| blue
gnd		| white 	| red
gnd		| green 	| blue
data	| red 		| yellow
5v		| yellow 	| brown
3.3v	| blue 		| white