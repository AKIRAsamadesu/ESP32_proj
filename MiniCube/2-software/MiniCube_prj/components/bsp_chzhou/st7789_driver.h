#include "esp_err.h"
#include <driver/spi_master.h>

#define HOST_ID SPI2_HOST
#define blk_pin 47 
#define cs1_pin 7 // For LCD chip select
// #define cs2_pin -1
#define dc_ctrl_pin 37
#define res_pin 38

#define mosi_pin 35
#define sclk_pin 36

#define LCD_WIDTH 240
#define LCD_HEIGHT 240
#define LCD_COLOR_DEPTH 16

#define rgb565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))
#define RED    rgb565(255,   0,   0) // 0xf800
#define GREEN  rgb565(  0, 255,   0) // 0x07e0
#define BLUE   rgb565(  0,   0, 255) // 0x001f
#define BLACK  rgb565(  0,   0,   0) // 0x0000
#define WHITE  rgb565(255, 255, 255) // 0xffff
#define GRAY   rgb565(128, 128, 128) // 0x8410
#define YELLOW rgb565(255, 255,   0) // 0xFFE0
#define CYAN   rgb565(  0, 156, 209) // 0x04FA
#define PURPLE rgb565(128,   0, 128) // 0x8010

void spi_init();
esp_err_t spi_write_byte(spi_device_handle_t SPIHandle, const uint8_t* Data, size_t DataLength);
esp_err_t spi_master_write_command(spi_device_handle_t SPIHandle, uint8_t cmd);
esp_err_t spi_master_write_data(spi_device_handle_t SPIHandle, uint8_t data, uint8_t length);

void lcd_init();
void lcd_fill_screen();