/*
  ESP32 Network Analyzer - Phase 1 (Network View)

  This sketch scans nearby 2.4 GHz WiFi networks and visualizes
  the signal strength (RSSI) of up to 10 networks as bars on a
  0.96" SSD1306 I2C OLED (128x64).

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
  display.println("WiFi Monitor");
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
  display.println("Scanning...");

  // --------- scan networks ----------
  // async = false, show_hidden = true
  int n = WiFi.scanNetworks(false, true);

  display.setCursor(0, 10);
  display.print("Found: ");
  display.println(n);

  // --------- draw RSSI bars for up to 10 networks ----------
  for (int i = 0; i < n && i < 10; i++) {
    int rssi = WiFi.RSSI(i);  // approx. -30 (strong) to -90 (weak)

    // Map RSSI to bar height (2..40 px)
    int h = map(rssi, -100, -30, 2, 40);
    if (h < 2
