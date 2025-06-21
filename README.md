<!--
 * @@ Author: ZhouCH
 * @@ Date: Do not edit
 * @@ LastEditors: ZhouCH
 * @@ LastEditTime: Do not edit
 * @@ FilePath: Do not edit
 * @@ Description: 
 * @@ License: MIT
-->

# LuaNode dev board

esp32-S3R8
下载的port名称： /dev/ttyACM0

ESP-IDF extension workflow:

1. ESP-IDF: Show Examples Projects / ESP-IDF: Create ESP-IDF project（后面还有一些选择设备信息的步骤自己看 https://github.com/espressif/vscode-esp-idf-extension/blob/master/docs/tutorial/basic_use.md）
2. ESP-IDF: Build your project（注意一定要在工程文件夹下！！！不能在上级文件夹中）
3. ESP-IDF: Select port to use（选择链接的串口或者USB口）
4. ESP-IDF: Flash your project（刷新内存）
5. ESP-IDF: Monitor your device（这个会通过串口在terminal中打印状态）

**ESP-IDF manually compilation workflow ( in terminal )**

1. . $HOME/esp/esp-idf/export.sh （构建esp编译环境每次启动都要构建一次）
2. idf.py build (编译工程)
3. idf.py set-target esp32s3 （设置编译对象SoC为esp32s3）
4. idf.py menuconfig （打开控制面板，可以在这里设置芯片的蓝牙和WIFI信息）
5. idf.py [-p /dev/ttyACM0] flash （设置程序烧写的串口，中间的-p设置不写的时候会使用系统默认找到的端口）
6. idf.py [-p /dev/ttyACM0] monitor (将开发板上的信息打印到terminal中，<font color=blue>不知道是什么端口输入的</font>)

**idf.py项目管理功能笔记**
URL：https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-guides/tools/idf-py.html

1. idf.py create-project {project name} (创建一个新的空工程只包括一个空的main.c)

2. idf.py create-component {component name} -C {component存放的文件夹} (创建一个组件文件夹这个文件夹的组建不能直接用，需要在CMakeLists中配置一下才能在main中使用)
   配置组件的方法：https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-guides/build-system.html#component-directories
   组件依赖实例：https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-guides/build-system.html#id22
    注意组件都统一放在components文件夹下并且创建各自私有的component文件夹
   
    如何使用自己的组件：
    s1: 用idf.py create-component创建组件
    s2: 如果是在主函数中使用，则需要在项目的CMakeLists.txt中的cmake_minimum_required和include之间声明设置EXTRA_COMPONENT_DIRS参数。即定义自己创建的components文件夹和在其下的组件
   
   ```
   set(EXTRA_COMPONENT_DIRS, "./components")
   ```
   
    s3: components文件夹下组件之间相互依赖，则在当前component的CMakeLists.txt中声明依赖的component
   
   ```
   idf_component_register(SRCS "LED.c"
                           INCLUDE_DIRS "include"
                           REQUIRES 依赖的component名称)
   ```
   
    s4: 自定义component需要API中的函数时需要用在component中的CMakeLists.txt中添加PREV_REQUIRES "driver"，这个driver就是esp-idf/components文件夹下的库文件夹的名称。然后再再头文件中包含自己需要的部件的头文件
   
   ```
   idf_component_register(SRCS "screen.c"
                   INCLUDE_DIRS "include"
                   PRIV_REQUIRES "driver")
   ```

FreeRTOS使用说明：https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/system/freertos.html
官方的freeRTOS是单核RTOS,而在IDF环境下支持的是多核版本

**备注**

1. 在回调函数中无法使用printf和ESP_LOGX替代的是ESP_DRAM_LOGX（其中X为）
2. 在app_main中，如果没有任何东西调用freeRTOS里的函数，在运行时就会触发看门狗事件。这个时候可以用vTaskDelay()消除这个问题
