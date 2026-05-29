#include <Arduino.h>
#include "BIOS.h"
#include "soundSystem.h"
#include "displaySystem.h"

#define BUZZER 21

enum SystemState {
  BIOS,
  BOOT
};

SystemState state = BIOS;

bool biosDone = false;
bool bootDone = false;

void setup() {
  Serial.begin(115200);

  Serial.println("ESP computer starting...");

  ledcAttach(BUZZER, 2000, 8);
  ledcWriteTone(BUZZER, 880);
  delay(250);
  ledcWriteTone(BUZZER, 0);
  delay(500);

  state = BIOS; 
}

void loop() {
  switch (state) {

    case BIOS:
      if (!biosDone) {
        soundSetup();
        Bsetup();
        biosDone = true;
        state = BOOT;
      }
      break;

    case BOOT:
      if (!bootDone) {
        displaySetup();
        bootDone = true;
      }

      soundLoop();
      break;
  }
}
