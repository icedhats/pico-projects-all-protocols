# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(timer_periodic_alarm C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(timer_periodic_alarm timer_periodic_alarm.c )

pico_set_program_name(timer_periodic_alarm "timer_periodic_alarm")
pico_set_program_version(timer_periodic_alarm "0.1")

pico_enable_stdio_uart(timer_periodic_alarm 1)
pico_enable_stdio_usb(timer_periodic_alarm 0)

# Add the standard library to the build
target_link_libraries(timer_periodic_alarm pico_stdlib)

pico_add_extra_outputs(timer_periodic_alarm)

