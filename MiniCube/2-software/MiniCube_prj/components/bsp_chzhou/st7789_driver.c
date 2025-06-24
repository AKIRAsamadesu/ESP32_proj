#include "st7789_driver.h"

#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <driver/spi_master.h>
#include <driver/gpio.h>
#include "esp_log.h"
#include "esp_err.h"

static spi_device_handle_t spi_handle;

void spi_init() {

    /*gpio configuration*/ 
    gpio_config_t gpio_conf;
    memset(&gpio_conf, 0, sizeof(gpio_conf));
    gpio_conf.mode=GPIO_MODE_OUTPUT;
    gpio_conf.pin_bit_mask=(1ULL<<blk_pin) | 
                            (1ULL<<cs1_pin) | 
                            (1ULL<<dc_ctrl_pin) | 
                            (1ULL<<res_pin) | 
                            (1ULL<<mosi_pin) | 
                            (1ULL<<sclk_pin);
    ESP_ERROR_CHECK(gpio_config(&gpio_conf));

    /*spi configuration*/
    spi_bus_config_t spi_bus_conf;
    memset(&spi_bus_conf, 0, sizeof(spi_bus_conf));
    spi_bus_conf.mosi_io_num=mosi_pin;
    spi_bus_conf.sclk_io_num=sclk_pin;
    spi_bus_conf.miso_io_num=-1;
    spi_bus_conf.quadhd_io_num=-1;
    spi_bus_conf.quadwp_io_num=-1;
    spi_bus_conf.flags=0;
    spi_bus_conf.max_transfer_sz=0;
    ESP_ERROR_CHECK(spi_bus_initialize(HOST_ID, &spi_bus_conf, SPI_DMA_CH_AUTO));

    spi_device_interface_config_t spi_interface_conf;
    memset(&spi_interface_conf, 0, sizeof(spi_interface_conf));
    spi_interface_conf.clock_speed_hz=20*1000*1000;
    spi_interface_conf.queue_size=7;
    spi_interface_conf.mode = 3;
	spi_interface_conf.flags = SPI_DEVICE_NO_DUMMY;
    spi_interface_conf.spics_io_num=cs1_pin;
    ESP_ERROR_CHECK(spi_bus_add_device(HOST_ID, &spi_interface_conf, &spi_handle));
}

esp_err_t spi_write_byte(spi_device_handle_t SPIHandle, const uint8_t* Data, size_t DataLength) {
    spi_transaction_t SPITransaction;
    if ( DataLength > 0 ) {
		memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
		SPITransaction.length = DataLength * 8;
		SPITransaction.tx_buffer = Data;
    }
    return spi_device_transmit(SPIHandle, &SPITransaction);
}

esp_err_t spi_master_write_command(spi_device_handle_t SPIHandle, uint8_t cmd) {
	static uint8_t Byte = 0;
	Byte = cmd;
	gpio_set_level(dc_ctrl_pin, 0);
	return spi_write_byte(SPIHandle, &Byte, 1);
}

esp_err_t spi_master_write_data(spi_device_handle_t SPIHandle, uint8_t data, uint8_t length) {
	static uint8_t Byte = 0;
	Byte = data;
	gpio_set_level(dc_ctrl_pin, 0);
	return spi_write_byte(SPIHandle, &Byte, length);
}

void lcd_init() {
    spi_master_write_command(spi_handle, 0x01);	//Software Reset
	vTaskDelay(pdMS_TO_TICKS(150));

	spi_master_write_command(spi_handle, 0x11);	//Sleep Out
	vTaskDelay(pdMS_TO_TICKS(255));
	
	spi_master_write_command(spi_handle, 0x3A);	//Interface Pixel Format
	spi_master_write_data(spi_handle, 0x55, 1);
	vTaskDelay(pdMS_TO_TICKS(10));
	
	spi_master_write_command(spi_handle, 0x36);	//Memory Data Access Control
	spi_master_write_data(spi_handle, 0x00, 1);

	spi_master_write_command(spi_handle, 0x2A);	//Column Address Set
	spi_master_write_data(spi_handle, 0x00, 1);
	spi_master_write_data(spi_handle, 0x00, 1);
	spi_master_write_data(spi_handle, 0x00, 1);
	spi_master_write_data(spi_handle, 0xF0, 1);

	spi_master_write_command(spi_handle, 0x2B);	//Row Address Set
	spi_master_write_data(spi_handle, 0x00, 1);
	spi_master_write_data(spi_handle, 0x00, 1);
	spi_master_write_data(spi_handle, 0x00, 1);
	spi_master_write_data(spi_handle, 0xF0, 1);

	spi_master_write_command(spi_handle, 0x21);	//Display Inversion On
	vTaskDelay(pdMS_TO_TICKS(10));

	spi_master_write_command(spi_handle, 0x13);	//Normal Display Mode On
	vTaskDelay(pdMS_TO_TICKS(10));

	spi_master_write_command(spi_handle, 0x29);	//Display ON
	vTaskDelay(pdMS_TO_TICKS(255));

    gpio_set_level(blk_pin, 1);
}

void lcd_fill_screen() 
{
	spi_master_write_command(spi_handle, 0x2A);	// set column(x) address
	spi_master_write_data(spi_handle, 0x00, 1);
	spi_master_write_data(spi_handle, 0x00, 1);
	spi_master_write_data(spi_handle, 0x00, 1);
	spi_master_write_data(spi_handle, 0x64, 1);

	spi_master_write_command(spi_handle, 0x2B);	// set Page(y) address
	spi_master_write_data(spi_handle, 0x00, 1);
	spi_master_write_data(spi_handle, 0x00, 1);
	spi_master_write_data(spi_handle, 0x00, 1);
	spi_master_write_data(spi_handle, 0x64, 1);
	
	spi_master_write_command(spi_handle, 0x2C);	// Memory Write
	static uint8_t color[2];
	color[0]=PURPLE>>8 & 0xff;
	color[1]=PURPLE & 0xff;
	
	for (int j=0; j<100; j++) {
		for (int i=0; i<100; ) {
			ESP_ERROR_CHECK(spi_master_write_data(spi_handle, color[0], 1));
			ESP_ERROR_CHECK(spi_master_write_data(spi_handle, color[1], 1));
		}
	}
	
}