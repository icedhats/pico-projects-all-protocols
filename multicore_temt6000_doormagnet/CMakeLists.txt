# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(multicore_temt6000_doormagnet C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(multicore_temt6000_doormagnet multicore_temt6000_doormagnet.c )

pico_set_program_name(multicore_temt6000_doormagnet "multicore_temt6000_doormagnet")
pico_set_program_version(multicore_temt6000_doormagnet "0.1")

pico_enable_stdio_uart(multicore_temt6000_doormagnet 1)
pico_enable_stdio_usb(multicore_temt6000_doormagnet 0)

# Add the standard library to the build
target_link_libraries(multicore_temt6000_doormagnet pico_stdlib pico_multicore hardware_adc hardware_pwm)

pico_add_extra_outputs(multicore_temt6000_doormagnet)

