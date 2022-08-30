# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(dc_motor_speed C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(dc_motor_speed dc_motor_speed.c )

pico_set_program_name(dc_motor_speed "dc_motor_speed")
pico_set_program_version(dc_motor_speed "0.1")

pico_enable_stdio_uart(dc_motor_speed 1)
pico_enable_stdio_usb(dc_motor_speed 0)

# Add the standard library to the build
target_link_libraries(dc_motor_speed pico_stdlib hardware_pwm)

pico_add_extra_outputs(dc_motor_speed)

