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
  display.println("Channel Load");
  display.display();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  delay(100);
}

void loop() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Channel Load");

  int chCount[15] = {0};   // channels 1..14

  int n = WiFi.scanNetworks(false, true);
  for (int i = 0; i < n; i++) {
    int ch = WiFi.channel(i);
    if (ch >= 1 && ch <= 14) {
      chCount[ch]++;
    }
  }

  // Draw channels 1..11 (most used on 2.4 GHz)
  for (int ch = 1; ch <= 11; ch++) {
    int count = chCount[ch];
    int h = count * 4;
    if (h > 40) h = 40;

    int x = (ch - 1) * 11;
    int barBottom = SCREEN_HEIGHT - 10;   // leave 10px for text
    int barTop = barBottom - h;

    // Bar
    display.fillRect(x, barTop, 9, h, WHITE);

    // Channel number under bar
    display.setTextSize(1);
    display.setCursor(x + 1, SCREEN_HEIGHT - 8);
    display.print(ch);
  }

  display.display();
  WiFi.scanDelete();
  delay(1500);
}
