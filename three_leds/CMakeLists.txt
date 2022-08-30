# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# # Pull in Raspberry Pi Pico SDK (must be before project)
# include(pico_sdk_import.cmake)

project(three_leds C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(three_leds three_leds.c )

pico_set_program_name(three_leds "three_leds")
pico_set_program_version(three_leds "0.1")

pico_enable_stdio_uart(three_leds 1)
pico_enable_stdio_usb(three_leds 0)

# Add the standard library to the build
target_link_libraries(three_leds pico_stdlib)

pico_add_extra_outputs(three_leds)

