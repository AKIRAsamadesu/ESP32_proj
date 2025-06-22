# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Espressif/frameworks/esp-idf-v5.2.1/components/bootloader/subproject"
  "C:/Users/50127/Desktop/Cubic Prj/3.ESP32_proj/MiniCube/2-software/MiniCube_prj/build/bootloader"
  "C:/Users/50127/Desktop/Cubic Prj/3.ESP32_proj/MiniCube/2-software/MiniCube_prj/build/bootloader-prefix"
  "C:/Users/50127/Desktop/Cubic Prj/3.ESP32_proj/MiniCube/2-software/MiniCube_prj/build/bootloader-prefix/tmp"
  "C:/Users/50127/Desktop/Cubic Prj/3.ESP32_proj/MiniCube/2-software/MiniCube_prj/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/50127/Desktop/Cubic Prj/3.ESP32_proj/MiniCube/2-software/MiniCube_prj/build/bootloader-prefix/src"
  "C:/Users/50127/Desktop/Cubic Prj/3.ESP32_proj/MiniCube/2-software/MiniCube_prj/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/50127/Desktop/Cubic Prj/3.ESP32_proj/MiniCube/2-software/MiniCube_prj/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/50127/Desktop/Cubic Prj/3.ESP32_proj/MiniCube/2-software/MiniCube_prj/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
