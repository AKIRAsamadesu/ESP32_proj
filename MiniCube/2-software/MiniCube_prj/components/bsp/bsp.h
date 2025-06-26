#pragma  once

#include <string.h>

#include "esp_vfs.h"
#include "esp_err.h"
#include "esp_spiffs.h"
#include "esp_log.h"

esp_err_t file_system_init();
void listSPIFFS(char * path);
