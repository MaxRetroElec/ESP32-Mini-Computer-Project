#include <TFT_eSPI.h>
#include <FS.h>
#include <LittleFS.h>

TFT_eSPI tft;

void Bsetup() {
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_WHITE);
    tft.setTextFont(2);
    tft.setTextSize(1);

    tft.println("### MAXENIX ESP BIOS BETA ###");
    tft.print(ESP.getFreeHeap());
    tft.println(" BYTES FREE");

    delay(2000);

    tft.println("");
    tft.println("READY");
    
    delay(500);

    tft.fillScreen(TFT_BLACK);
}