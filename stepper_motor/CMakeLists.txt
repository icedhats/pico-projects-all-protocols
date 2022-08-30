# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(stepper_motor C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(stepper_motor stepper_motor.c )

pico_set_program_name(stepper_motor "stepper_motor")
pico_set_program_version(stepper_motor "0.1")

pico_enable_stdio_uart(stepper_motor 1)
pico_enable_stdio_usb(stepper_motor 0)

# Add the standard library to the build
target_link_libraries(stepper_motor pico_stdlib)

pico_add_extra_outputs(stepper_motor)

