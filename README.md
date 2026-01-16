# ESP32 Network Analyzer

The **ESP32 Network Analyzer** is a handheld WiFi monitor built using an ESP32 and a 0.96" OLED display. This tool scans nearby WiFi networks and offers two distinct viewing modes: a detailed network list with signal strength (Phase 1) and a channel crowdiness visualizer (Phase 2).

---

## 🚀 Features

* **Phase 1 – Network View**: Scans and identifies nearby 2.4 GHz WiFi networks.
* It displays each network's SSID and RSSI (signal strength) directly on the OLED screen.
* **Phase 2 – Channel View**: Analyzes the environment by grouping detected networks into their respective channels (1–11).
* It uses bar graphs to represent the crowdiness of each channel, helping identify the best frequencies for your own network.

## 🛠️ Hardware & Wiring

This project requires a standard ESP32 development board and a common I2C display.

* **ESP32 Development Board** (DevKit style).
* **0.96" I2C OLED Display** (SSD1306, 128×64).
* **USB Cable** for power and firmware programming.
* **Jumper Wires** and a breadboard for assembly.

### Default Pin Mapping

| OLED Pin | ESP32 Pin | Function |
| --- | --- | --- |
| **VCC** | 3V3 | Power |
| **GND** | GND | Ground |
| **SDA** | GPIO 21 | I2C Data |
| **SCL** | GPIO 22 | I2C Clock |

## 📂 Project Structure

* `src/`: Contains the latest main code for the Phase 2 channel analyzer.
* `archive/phase1/`: Contains the earlier version focused on network listing and RSSI.
* `docs/`: Extra documentation, including wiring notes and images.

## 🏁 Getting Started

1. **Environment Setup**: Install the Arduino IDE and add ESP32 support via the Boards Manager by installing **“ESP32 by Espressif Systems”**.
2. **Libraries**: Install the `Adafruit_SSD1306` and `Adafruit_GFX` libraries through the Library Manager.
3. **Upload**: Select your ESP32 board and the correct COM port. Click **Upload** (recommended speed: **921600**).

## 🔮 Future Work

* Add battery support (Li-ion) for fully portable use.
* Design and 3D-print a custom enclosure.
* Improve the UI with physical buttons to toggle between Phase 1 and Phase 2.

---

## 📚 Credits & References

This project was built using the following resources and inspirations:

* **Core Framework**: [Official ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)
* **OLED Tutorials**: [Random Nerd Tutorials](https://randomnerdtutorials.com/esp32-ssd1306-oled-display-arduino-ide/)
* **Scanner Inspiration**: [CyberTechNex WiFi Scanner](https://github.com/CyberTechNex/ESP32-WIFI-Scanner)
* **Channel Visualizer Logic**: [hackffm ESP32 Scanner](https://github.com/hackffm/ESP32_OLED_WifiScanner)
* **Walkthrough Video**: [HaZBxCuhPfE on YouTube](https://www.youtube.com/watch?v=HaZBxCuhPfE)

---