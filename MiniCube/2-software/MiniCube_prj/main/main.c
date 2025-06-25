#include <stdio.h>
#include <string.h>

#include "task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

void app_main(void)
{
    const char* TAG="MainTask";
    
    ESP_LOGI(TAG, "display_task is started...");
    xTaskCreate(display_task, "display_task", 1024*6, NULL, 3, NULL);
}
