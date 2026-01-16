#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 failed");
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("WiFi Monitor");
  display.display();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  delay(100);
}

void loop() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Scanning...");

  int n = WiFi.scanNetworks(false, true);  // async=false, show_hidden=true

  display.setCursor(0, 10);
  display.print("Found: ");
  display.println(n);

  // Draw up to 10 bars representing signal strength
  for (int i = 0; i < n && i < 10; i++) {
    int rssi = WiFi.RSSI(i);          // e.g. -30 (strong) to -90 (weak)
    int h = map(rssi, -100, -30, 2, 40);
    if (h < 2) h = 2;
    if (h > 40) h = 40;

    int x = i * 12;
    display.fillRect(x, SCREEN_HEIGHT - h, 10, h, WHITE);
  }

  display.display();

  WiFi.scanDelete();
  delay(1000);
}
