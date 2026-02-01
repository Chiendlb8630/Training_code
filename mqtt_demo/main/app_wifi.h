#pragma once

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#define ESP_WIFI_SSID      "Ula Working Space" // chỗ nhập wifi
#define ESP_WIFI_PASS      "79797979"          // Chỗ nhập mật khẩu wifi.
#define LED_GPIO           2
#define MAXIMUM_RETRY      5

#define TAG                "wifi_module"
void app_wifi_init(void);


