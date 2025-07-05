idf_component_register(SRCS "bsp.c"
                       INCLUDE_DIRS "."
                       REQUIRES vfs spiffs st7789 pngle)