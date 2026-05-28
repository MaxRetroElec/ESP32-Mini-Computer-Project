#include <Arduino.h>
#include "BIOS.h"
#include "soundSystem.h"
#include "displaySystem.h"

#define BUZZER 21

void setup() {
  Serial.begin(115200);

  Serial.println("ESP computer starting...");

  ledcAttach(BUZZER, 2000, 8);
  ledcWriteTone(BUZZER, 880);
  delay(250);
  ledcWriteTone(BUZZER, 0);
  delay(500);

  Bsetup();

  soundSetup();
  displaySetup();
}

void loop() {
  soundLoop();
}