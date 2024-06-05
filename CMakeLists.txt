cmake_minimum_required(VERSION 3.22)

# Verify the value of CC
message("CC: $ENV{CC}")

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME F407)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

file(GLOB_RECURSE LVGL_SRCS "LVGL/*.c")
file(GLOB_RECURSE GUI_SRCS "GUI_SquareLine_Gen/*.c")
# Add sources to executable

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ./ExtraDrivers/lcd.c
    ./ExtraDrivers/softiic.c
    ./ExtraDrivers/CH455.c
    ./ExtraDrivers/w25qxx.c
    ./ExtraDrivers/key.c
    ./ExtraDrivers/ct_iic.c
    ./ExtraDrivers/gt9147.c
    ./ExtraDrivers/GNSS.c
    ${LVGL_SRCS}
    ${GUI_SRCS}
    # Add user sources here
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ./ExtraDrivers
    ./LVGL
    ./LVGL/src
    ./LVGL/porting
    ./GUI_SquareLine_Gen
    # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
    LV_LVGL_H_INCLUDE_SIMPLE
    LV_CONF_INCLUDE_SIMPLE
)
# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    # Add user defined libraries
)

#添加链接选项以启用printf float
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -u_printf_float
)
