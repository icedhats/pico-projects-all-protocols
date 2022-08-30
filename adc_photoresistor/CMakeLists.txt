# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# # Pull in Raspberry Pi Pico SDK (must be before project)
# include(pico_sdk_import.cmake)

project(adc_photoresistor C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(adc_photoresistor adc_photoresistor.c logger_uart_blocking.c)

pico_set_program_name(adc_photoresistor "adc_photoresistor")
pico_set_program_version(adc_photoresistor "0.1")

pico_enable_stdio_uart(adc_photoresistor 1)
pico_enable_stdio_usb(adc_photoresistor 0)

# Add the standard library to the build
target_link_libraries(adc_photoresistor pico_stdlib hardware_adc)

pico_add_extra_outputs(adc_photoresistor)

