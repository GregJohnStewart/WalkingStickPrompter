# WalkingStickPrompter

A walking stick tele-prompter.

## Usage

With the 

## Build Documentation

### Bill of Materials

- [Adafruit Feather 328P](https://learn.adafruit.com/adafruit-feather-328p-atmega328-atmega328p/overview)
- [2.2" 18-bit color TFT LCD display with microSD card breakout](https://www.adafruit.com/product/1480)

### Resources

- [Adafruit Feather 328P Pinouts](https://learn.adafruit.com/adafruit-feather-328p-atmega328-atmega328p/pinouts)
- [Adafruit 2.2" TFT Display with SD Card Reader](https://learn.adafruit.com/2-2-tft-display)
- [Adafruit ILI9341 Arduino Library](https://github.com/adafruit/Adafruit_ILI9341)
- [Adafruit TFT Display Example](https://github.com/adafruit/Adafruit_ILI9341/blob/master/examples/graphicstest/graphicstest.ino)

### Environment Setup

1. Arduino IDE Setup
   1. Board Selection
      - Board: `Arduino Pro or Arduino Pro Mini`
      - Processor: `ATMega328P (3.3V, 8 MHz)`
   2. Required Libs
      - [Adafruit BusIO Library](https://github.com/adafruit/Adafruit_BusIO)
      - [AdaFruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
      - [Adafruit ILI9341 Library](https://github.com/adafruit/Adafruit_ILI9341)

### Circuitry

Realistic circuit diagram:

![Realistic circuitry view](Circuit Diagram_bb.png)

Schematic view:

![Schematic View](Circuit Diagram_schem.png)

### Additional

#### Fritzing

Requires the addition of the Adafruit resource pack:

https://learn.adafruit.com/using-the-adafruit-library-with-fritzing/import-the-library-into-fritzing

