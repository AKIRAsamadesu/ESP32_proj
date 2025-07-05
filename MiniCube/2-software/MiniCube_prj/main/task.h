#pragma once
#include <stdio.h>
#include "st7789.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "bsp.h"

#define MOSI_GPIO 35
#define SCLK_GPIO 36
#define CS_GPIO 7
#define DC_GPIO 37
#define RESET_GPIO 38
#define BL_GPIO 47
#define CONFIG_WIDTH 240
#define CONFIG_HEIGHT 240
#define CONFIG_OFFSETX 0
#define CONFIG_OFFSETY 0

void display_task(void* param);

