#include "task.h"

void display_task(void* param) {
    static const char *TAG="display_task";
    
    ESP_ERROR_CHECK(file_system_init());

    while(1) {
        // lcd_fill_screen();
        ESP_LOGI(TAG, "flash!");
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
