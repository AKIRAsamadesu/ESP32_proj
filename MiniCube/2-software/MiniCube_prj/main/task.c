#include "task.h"

void display_task(void* param) {
    // static const char *TAG="display_task";
    
    ESP_ERROR_CHECK(file_system_init());
    TFT_t dev;
    spi_master_init(&dev, MOSI_GPIO, SCLK_GPIO, CS_GPIO, DC_GPIO, RESET_GPIO, BL_GPIO);
	lcdInit(&dev, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY);

    listSPIFFS("/img");
    char file[32];
    ESP_LOGI(__FUNCTION__, "flash!");
    strcpy(file, "/img/web03.png");
    
    while(1) {
        // showPNG(&dev, file, CONFIG_WIDTH, CONFIG_HEIGHT);
        lcdFillScreen(&dev, RED);
        lcdDrawFinish(&dev);
        vTaskDelay(pdMS_TO_TICKS(1000));
        lcdFillScreen(&dev, GREEN);
        lcdDrawFinish(&dev);
        vTaskDelay(pdMS_TO_TICKS(1000));
        lcdFillScreen(&dev, YELLOW);
        lcdDrawFinish(&dev);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
