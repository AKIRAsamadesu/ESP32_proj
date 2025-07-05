#pragma  once

#include <string.h>

#include "esp_vfs.h"
#include "esp_err.h"
#include "esp_spiffs.h"
#include "esp_log.h"
#include "st7789.h"
#include "pngle.h"
#include "decode_png.h"

esp_err_t file_system_init();
void listSPIFFS(char * path);
void showPNG(TFT_t * dev, char * file, int width, int height);