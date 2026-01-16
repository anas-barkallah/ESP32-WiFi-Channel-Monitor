# Wiring Guide

This document describes the electrical connections for the ESP32 Network Analyzer.

## Components

- ESP32 DevKit-style development board (3.3 V logic)
- 0.96" OLED display, SSD1306 controller, I2C interface, address 0x3C
- USB cable for powering/programming the ESP32
- Breadboard and male–male jumper wires

## Pin Mapping

| OLED Pin | ESP32 Pin | Notes                                   |
|---------|-----------|-----------------------------------------|
| VCC     | 3V3       | 3.3 V supply from ESP32 (do NOT use 5 V) |
| GND     | GND       | Common ground                           |
| SDA     | GPIO 21   | I2C data (default ESP32 SDA)            |
| SCL     | GPIO 22   | I2C clock (default ESP32 SCL)           |

## Notes

- The OLED uses the I2C address `0x3C` by default; this value is used in the code.  
- Make sure all grounds (ESP32, OLED, any external modules) are connected together.  
- If you use a different ESP32 board, SDA/SCL pins can be changed in the code and rewired accordingly.  
- Keep wire lengths short to avoid noise on the I2C lines.
