#include "soundSystem.h"
#include <LittleFS.h>
#include "driver/i2s.h"

File audio;

#define I2S_PORT I2S_NUM_0

#define I2S_BCLK 26
#define I2S_LRC  27
#define I2S_DOUT 25

#define SAMPLE_RATE 16000

void setupI2S() {
  i2s_config_t config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = 128,
    .use_apll = false,
    .tx_desc_auto_clear = true,
    .fixed_mclk = 0
  };

  i2s_pin_config_t pins = {
    .bck_io_num = I2S_BCLK,
    .ws_io_num = I2S_LRC,
    .data_out_num = I2S_DOUT,
    .data_in_num = I2S_PIN_NO_CHANGE
  };

  i2s_driver_install(I2S_PORT, &config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pins);
  i2s_zero_dma_buffer(I2S_PORT);
}

void soundSetup() {

  if (!LittleFS.begin()) {
    Serial.println("LittleFS FAIL");
    return;
  }

  audio = LittleFS.open("/MarbleZone.wav", "r");

  if (!audio) {
    Serial.println("WAV NOT FOUND");
    return;
  }

  audio.seek(44);

  setupI2S();
}

void soundLoop() {

  if (!audio.available()) {
    audio.seek(44);
    return;
  }

  int16_t monoBuffer[128];
  int16_t stereoBuffer[256];

  size_t bytesRead = audio.read((uint8_t*)monoBuffer, sizeof(monoBuffer));

  int samples = bytesRead / 2;

  for (int i = 0; i < samples; i++) {
    int16_t s = monoBuffer[i] / 4;
    stereoBuffer[i * 2] = s;
    stereoBuffer[i * 2 + 1] = s;
  }

  size_t bytesWritten;

  i2s_write(
    I2S_PORT,
    stereoBuffer,
    samples * 4,
    &bytesWritten,
    portMAX_DELAY
  );
}