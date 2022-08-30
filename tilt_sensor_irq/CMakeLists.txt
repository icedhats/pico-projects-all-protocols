# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(tilt_sensor_irq C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(tilt_sensor_irq tilt_sensor_irq.c logger_uart_blocking.c)

pico_set_program_name(tilt_sensor_irq "tilt_sensor_irq")
pico_set_program_version(tilt_sensor_irq "0.1")

pico_enable_stdio_uart(tilt_sensor_irq 1)
pico_enable_stdio_usb(tilt_sensor_irq 0)

# Add the standard library to the build
target_link_libraries(tilt_sensor_irq pico_stdlib)

pico_add_extra_outputs(tilt_sensor_irq)

