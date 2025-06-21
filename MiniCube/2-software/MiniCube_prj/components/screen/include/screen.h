#include "log.h"
#include "driver/spi_master.h"

void spi_init(void);
void screen_init(void);
void write_data_to_screen();

#define spi_clk_d0          1
#define spi_data_d1         2
#define spi_res             3 // chip reset
#define spi_dc              4 // data or command select
#define spi_cs              5 // chip select
#define disable             -1

static const char *TAG = "spi-debug-report";     