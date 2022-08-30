# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(spi_lcd_0_96 C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_subdirectory(lib/Config)
add_subdirectory(lib/LCD)
add_subdirectory(lib/Fonts)
add_subdirectory(lib/GUI)

include_directories(./lib/Config)
include_directories(./lib/GUI)
include_directories(./lib/LCD)

add_executable(spi_lcd_0_96 spi_lcd_0_96.c )

pico_set_program_name(spi_lcd_0_96 "spi_lcd_0_96")
pico_set_program_version(spi_lcd_0_96 "0.1")

pico_enable_stdio_uart(spi_lcd_0_96 1)
pico_enable_stdio_usb(spi_lcd_0_96 0)

# Add the standard library to the build
target_link_libraries(spi_lcd_0_96 pico_stdlib hardware_spi hardware_adc LCD GUI Fonts Config)

pico_add_extra_outputs(spi_lcd_0_96)

