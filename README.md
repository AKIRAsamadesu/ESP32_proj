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
���ص�port���ƣ� /dev/ttyACM0

ESP-IDF extension workflow:

1. ESP-IDF: Show Examples Projects / ESP-IDF: Create ESP-IDF project�����滹��һЩѡ���豸��Ϣ�Ĳ����Լ��� https://github.com/espressif/vscode-esp-idf-extension/blob/master/docs/tutorial/basic_use.md��
2. ESP-IDF: Build your project��ע��һ��Ҫ�ڹ����ļ����£������������ϼ��ļ����У�
3. ESP-IDF: Select port to use��ѡ�����ӵĴ��ڻ���USB�ڣ�
4. ESP-IDF: Flash your project��ˢ���ڴ棩
5. ESP-IDF: Monitor your device�������ͨ��������terminal�д�ӡ״̬��

**ESP-IDF manually compilation workflow ( in terminal )**

1. . $HOME/esp/esp-idf/export.sh ������esp���뻷��ÿ��������Ҫ����һ�Σ�
2. idf.py build (���빤��)
3. idf.py set-target esp32s3 �����ñ������SoCΪesp32s3��
4. idf.py menuconfig ���򿪿�����壬��������������оƬ��������WIFI��Ϣ��
5. idf.py [-p /dev/ttyACM0] flash �����ó�����д�Ĵ��ڣ��м��-p���ò�д��ʱ���ʹ��ϵͳĬ���ҵ��Ķ˿ڣ�
6. idf.py [-p /dev/ttyACM0] monitor (���������ϵ���Ϣ��ӡ��terminal�У�<font color=blue>��֪����ʲô�˿������</font>)

**idf.py��Ŀ�����ܱʼ�**
URL��https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-guides/tools/idf-py.html

1. idf.py create-project {project name} (����һ���µĿչ���ֻ����һ���յ�main.c)

2. idf.py create-component {component name} -C {component��ŵ��ļ���} (����һ������ļ�������ļ��е��齨����ֱ���ã���Ҫ��CMakeLists������һ�²�����main��ʹ��)
   ��������ķ�����https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-guides/build-system.html#component-directories
   �������ʵ����https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-guides/build-system.html#id22
    ע�������ͳһ����components�ļ����²��Ҵ�������˽�е�component�ļ���
   
    ���ʹ���Լ��������
    s1: ��idf.py create-component�������
    s2: ���������������ʹ�ã�����Ҫ����Ŀ��CMakeLists.txt�е�cmake_minimum_required��include֮����������EXTRA_COMPONENT_DIRS�������������Լ�������components�ļ��к������µ����
   
   ```
   set(EXTRA_COMPONENT_DIRS, "./components")
   ```
   
    s3: components�ļ��������֮���໥���������ڵ�ǰcomponent��CMakeLists.txt������������component
   
   ```
   idf_component_register(SRCS "LED.c"
                           INCLUDE_DIRS "include"
                           REQUIRES ������component����)
   ```
   
    s4: �Զ���component��ҪAPI�еĺ���ʱ��Ҫ����component�е�CMakeLists.txt�����PREV_REQUIRES "driver"�����driver����esp-idf/components�ļ����µĿ��ļ��е����ơ�Ȼ������ͷ�ļ��а����Լ���Ҫ�Ĳ�����ͷ�ļ�
   
   ```
   idf_component_register(SRCS "screen.c"
                   INCLUDE_DIRS "include"
                   PRIV_REQUIRES "driver")
   ```

FreeRTOSʹ��˵����https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-reference/system/freertos.html
�ٷ���freeRTOS�ǵ���RTOS,����IDF������֧�ֵ��Ƕ�˰汾

**��ע**

1. �ڻص��������޷�ʹ��printf��ESP_LOGX�������ESP_DRAM_LOGX������XΪ��
2. ��app_main�У����û���κζ�������freeRTOS��ĺ�����������ʱ�ͻᴥ�����Ź��¼������ʱ�������vTaskDelay()�����������
