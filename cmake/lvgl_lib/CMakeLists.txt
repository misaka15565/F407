cmake_minimum_required(VERSION 3.22)

project(lvgl_lib)
add_library(lvgl_lib INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(stm32cubemx INTERFACE 
	USE_HAL_DRIVER 
	STM32F407xx
    $<$<CONFIG:Debug>:DEBUG>
    LV_LVGL_H_INCLUDE_SIMPLE
    LV_CONF_INCLUDE_SIMPLE
)

target_include_directories(lvgl_lib INTERFACE
    ../../LVGL

)

file(GLOB_RECURSE LVGL_SRCS "../../LVGL/*.c")

target_sources(lvgl_lib INTERFACE
    ${LVGL_SRCS}
)


target_link_directories(lvgl_lib INTERFACE
)

target_link_libraries(lvgl_lib INTERFACE
)
