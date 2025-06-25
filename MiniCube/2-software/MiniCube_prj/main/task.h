#pragma once

#include "st7789.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "bsp.h"

void display_task(void* param);

