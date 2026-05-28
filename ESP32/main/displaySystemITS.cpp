#include <TFT_eSPI.h>
#include <FS.h>
#include <LittleFS.h>
#include "tft.h"

#define IMG_W 200
#define IMG_H 74

uint16_t imgBuffer[IMG_W * IMG_H];

void displaySetup() {
  
  tft.setTextColor(TFT_WHITE);
  tft.setTextFont(1);
  tft.setTextSize(1);

  if (!LittleFS.begin(true)) {
    Serial.println("LittleFS mount FAILED");
    return;
  }

  Serial.println("LittleFS OK");

  fs::File f = LittleFS.open("/image.bin", "r");

  if (!f) {
    Serial.println("ERROR: /image.bin not found");
    return;
  }

  Serial.print("File size: ");
  Serial.println(f.size());

  size_t expectedSize = IMG_W * IMG_H * 2;

  size_t bytes = f.read((uint8_t*)imgBuffer, expectedSize);
  f.close();

  Serial.print("Bytes read: ");
  Serial.println(bytes);

  int x = (tft.width() - IMG_W) / 2;
  int y = (tft.height() - IMG_H) / 2 - 10;

  tft.setSwapBytes(true);

  tft.pushImage(x, y, IMG_W, IMG_H, imgBuffer);

  tft.setCursor(10, 230);
  tft.println("Playing <Marble_zone.bin>.");

  Serial.println("Image displayed");
}

void displayLoop() {
}