ESP32s3有4个SPI外设：

SPI0/1是专用SPI, 主要供内部使用以访问外部flash 及PSRAM。

SPI2/3是通用SPI, 可以用于控制显示屏等外设

1. 初始化
   
   ```c
   void func_spi2_init(void) {
   
       spi_bus_config_t spi_config;
   
       spi_config.mosi_io_num = mosi_pin;
   
       spi_config.sclk_io_num = sclk_pin;
   
       spi_config.miso_io_num = -1;
   
       spi_config.quadwp_io_num = -1;
   
       spi_config.quadhd_io_num = -1;
   
       spi_config.flags = SPICOMMON_BUSFLAG_MASTER;
   
       spi_config.max_transfer_sz = 40*1000*1000*40*sizeof(uint16_t);
   
       ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &spi_config, SPI_DMA_CH_AUTO));
   
   }
   ```

    对于spi的传输频率：

    主机模式下时钟频率最大80MHz，从机下最大60MHz

  2. 传输

    CPU模式下每一次传输都要从buffer（SPI_W0_REG~SPI_W15_REG，32bit）中拿数据，或者接受数据放在buffer中，每一次传输都要配置寄存器，动作由CPU触发（这种方式只能单次传输）

    传输的时候是从16个buffer中轮流拿数据或者取数据，每个字节为8位对应一个地址，每收/发一次TX,RX指针往前移一个地址，一个register中有4个字节，SPI_W0_REG~SPI_W7_REG有64个字节

    在DMA模式下（DMA1，DMA2）可以

    - 单次传输

    - 连续传输

    - 分段配置传输

    从由GDMA控制DMA连接的内存中发送数据，或者接收数据到DMA内存中。  （需要配置GDMA）






