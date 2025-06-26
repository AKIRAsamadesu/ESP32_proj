#include "task.h"

void display_task(void* param) {
    static const char *TAG="display_task";
    
    ESP_ERROR_CHECK(file_system_init());
    TFT_t dev;
    spi_master_init(&dev, MOSI_GPIO, SCLK_GPIO, CS_GPIO, DC_GPIO, RESET_GPIO, BL_GPIO);
	lcdInit(&dev, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY);

    listSPIFFS("/img");
    char file[32];
    while(1) {
        // lcd_fill_screen();
        ESP_LOGI(TAG, "flash!");
        
        strcpy(file, "/img/web03.png");
         
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}
