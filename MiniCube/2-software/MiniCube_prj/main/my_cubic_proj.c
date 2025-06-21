#include <stdio.h>
#include "screen.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

void app_main(void)
{
    ///////////////////
    //  SCREEN TASK  //
    ///////////////////
    
    //////////////////////
    //  BLUETOOTH TASK  //
    //////////////////////

    /////////////////
    //  WIFI TASK  //
    /////////////////

    /////////////////////////////
    //  GYROSCOPE SENSOR TASK  //
    /////////////////////////////

    ////////////////
    //  KEY TASK  //
    ////////////////

    /////////////////////////////
    //  POWER MAMAGEMENT TASK  //
    /////////////////////////////
    
    while(1)
    {
        vTaskDelay(10);
    }
}
