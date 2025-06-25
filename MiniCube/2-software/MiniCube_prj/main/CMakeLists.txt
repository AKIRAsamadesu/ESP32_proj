idf_component_register(SRCS "task.c" "main.c"
                       INCLUDE_DIRS "."
                       REQUIRES st7789 bsp driver)
