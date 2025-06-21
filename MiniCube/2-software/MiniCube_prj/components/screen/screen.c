#include <stdio.h>
#include "screen.h"

void spi_init(void)
{
    // BUS configure
    // spi_bus_config_t buscfg={
    //     .miso_io_num = disable,
    //     .mosi_io_num = spi_data_d1,
    //     .sclk_io_num = spi_clk_d0,
    //     .quadwp_io_num = disable,
    //     .quadhd_io_num = disable,
    //     .max_transfer_sz = SOC_SPI_MAXIMUM_BUFFER_SIZE, // DMA is disabled
    // };

    // spi_bus_initialize(,&buscfg,)

    // device configure

    // transaction configure
}

void write_data_to_screen(uint8_t content)
{

}

void screen_init(void)
{

}