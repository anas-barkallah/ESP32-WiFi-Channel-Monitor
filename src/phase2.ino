/*
  ESP32 Network Analyzer - Phase 2 (Channel View)

  This sketch scans nearby 2.4 GHz WiFi networks and visualizes how
  crowded channels 1–11 are on a 0.96" SSD1306 I2C OLED (128x64).

  Hardware:
    - ESP32 DevKit-style board
    - 0.96" SSD1306 OLED, I2C, address 0x3C
      VCC -> 3V3, GND -> GND, SDA -> GPIO 21, SCL -> GPIO 22

  Libraries:
    - Wire
    - Adafruit_GFX
    - Adafruit_SSD1306
    - WiFi (ESP32 core)
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 failed");
    for(;;);  // Halt if display init fails
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Channel Load");
  display.display();

  // Initialize WiFi in station mode (no AP)
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  delay(100);
}

void loop() {
  // --------- UI header ----------
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Channel Load");

  // --------- aggregate: count networks per channel ----------
  int chCount[15] = {0};   // channels 1..14 (index = channel number)

  // active scan; showHidden=true to also include hidden SSIDs
  int n = WiFi.scanNetworks(false, true);
  for (int i = 0; i < n; i++) {
    int ch = WiFi.channel(i);
    if (ch >= 1 && ch <= 14) {
      chCount[ch]++;
    }
  }

  // --------- draw: bars for channels 1..11 ----------
  for (int ch = 1; ch <= 11; ch++) {
    int count = chCount[ch];

    // Map "number of networks" to bar height (max ~40 px)
    int h = count * 4;
    if (h > 40) h = 40;

    int x = (ch - 1) * 11;        // bar position on X axis
    int barBottom = SCREEN_HEIGHT - 10;  // leave 10 px for text
    int barTop = barBottom - h;

    // Bar
    display.fillRect(x, barTop, 9, h, WHITE);

    // Channel number under bar
    display.setTextSize(1);
    display.setCursor(x + 1, SCREEN_HEIGHT - 8);
    display.print(ch);
  }

  // --------- push frame + cleanup ----------
  display.display();
  WiFi.scanDelete();
  delay(1500);
}
