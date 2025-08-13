#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define PIR_POWER_PIN 18
#define PIR_SIGNAL_PIN 4

void app_main(void) {
  gpio_reset_pin(PIR_POWER_PIN);
  gpio_reset_pin(PIR_SIGNAL_PIN);

  gpio_set_direction(PIR_POWER_PIN, GPIO_MODE_OUTPUT);
  gpio_set_direction(PIR_SIGNAL_PIN, GPIO_MODE_INPUT);

  gpio_pulldown_en(PIR_SIGNAL_PIN);

  gpio_set_level(PIR_POWER_PIN, 1);

  ESP_LOGI("PIR", "Application started - PIR sensor powered");

  while (1) {
    int motion_detected = gpio_get_level(PIR_SIGNAL_PIN);

    if (motion_detected) {
      ESP_LOGI("PIR", "Motion detected!");
    } else {
      ESP_LOGI("PIR", "No motion");
    }

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
