# SNES to GameCube adapter

![Image of adapter](headerImage.jpg)
Code for building a SNES to GameCube controller adapter.
Also works with the 8Bitdo [Retro Receiver](http://www.8bitdo.com/retro-receiver-snes/)

## Button Mapping

| SNES Button | GameCube Mapping               | Notes                              |
| ----------- | ------------------------------ | ---------------------------------- |
| A           | A                              |
| B           | B                              |
| X           | X                              |
| Y           | Y                              |
| Select      | Y                              | Like SNES Hori-pad / for GBA games |
| Start       | Start                          |
| L           | L (digital), L (analog: 0/255) | Analog: 255 if pressed, 0 if not   |
| R           | R (digital), R (analog: 0/255) | Analog: 255 if pressed, 0 if not   |
| L+R+Select  | Z                              |
| D-Pad Left  | D-Pad Left                     |
| D-Pad Up    | D-Pad Up                       |
| D-Pad Right | D-Pad Right                    |
| D-Pad Down  | D-Pad Down                     |

## Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/Main/Software) (tested on 2.3.6)
- [Arduino Nintendo Library](https://github.com/NicoHood/Nintendo) by NicoHood (tested on 1.4.0)

## Hardware

### Parts

- Logic Level Converter 5v <-> 3.3v
- Arduino Pro Mini (5v 16MHz)
- USB -> Serial adapter if your Arduino comes without USB.
- 1kΩ Resistor
- Female SNES controller port (SNES extension cable)
- Male GameCube controller connector (GameCube extension cable)

### Wiring

![Wiring diagram](snesToGameCube_bb.png)

The colors of the wires in the cables may not match between the original controller and the extension cable, below is the mapping for my cables the colors may be different for you.

#### SNES pinout

| Type  | Original Controller | Extension Cable |
| ----- | ------------------- | --------------- |
| 5v    | white               | green           |
| clock | yellow              | yellow          |
| latch | orange              | white           |
| data  | red                 | red             |
| gnd   | brown               | black           |

#### GameCube Pinout

| Type | Original Controller | Extension Cable |
| ---- | ------------------- | --------------- |
| gnd  | Black               | blue            |
| gnd  | white               | red             |
| gnd  | green               | blue            |
| data | red                 | yellow          |
| 5v   | yellow              | brown           |
| 3.3v | blue                | white           |
