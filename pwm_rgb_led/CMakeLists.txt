# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(pwm_rgb_led C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(pwm_rgb_led pwm_rgb_led.c )

pico_set_program_name(pwm_rgb_led "pwm_rgb_led")
pico_set_program_version(pwm_rgb_led "0.1")

pico_enable_stdio_uart(pwm_rgb_led 1)
pico_enable_stdio_usb(pwm_rgb_led 0)

# Add the standard library to the build
target_link_libraries(pwm_rgb_led pico_stdlib hardware_pwm)

pico_add_extra_outputs(pwm_rgb_led)

