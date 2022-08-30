# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(i2c_oled_9_6_lm75a C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(i2c_oled_9_6_lm75a i2c_oled_9_6_lm75a.cpp M2M_LM75a.cpp)
add_subdirectory(pico-ss-oled build)

pico_set_program_name(i2c_oled_9_6_lm75a "i2c_oled_9_6_lm75a")
pico_set_program_version(i2c_oled_9_6_lm75a "0.1")

pico_enable_stdio_uart(i2c_oled_9_6_lm75a 1)
pico_enable_stdio_usb(i2c_oled_9_6_lm75a 0)

# Add the standard library to the build
target_link_libraries(i2c_oled_9_6_lm75a pico_stdlib pico_ss_oled)

pico_add_extra_outputs(i2c_oled_9_6_lm75a)

