#include <stdio.h>
#include <string.h>

#include "st7789_driver.h"
// #include "st7789.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

// void task_A(void* param)
// {
//     static const char* TAG="Task_A";
//     TFT_t dev;

//     spi_master_init(&dev, mosi_pin, sclk_pin, cs1_pin, dc_ctrl_pin, res_pin, blk_pin);
// 	lcdInit(&dev, LCD_WIDTH, LCD_HEIGHT, 0, 0);

//     while(1)
//     {
//         ESP_LOGI(TAG, "This is a sentence displayed by ESP");
//         vTaskDelay(pdMS_TO_TICKS(1000));
//     }
// }

void task_B(void* param) {
    static const char *TAG="Task B";
    spi_init();
    lcd_init();
    while(1) {
        // lcd_fill_screen();
        ESP_LOGI(TAG, "flash!");
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void app_main(void)
{
    const char* TAG="MainTask";
    
    ESP_LOGI(TAG, "task_B is started...");
    // xTaskCreate(task_A, "Task1", 1024*6, NULL, 3, NULL);
    xTaskCreate(task_B, "Task2", 1024*6, NULL, 3, NULL);
}
