cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# Initialize the SDK
pico_sdk_init()

include(example_auto_set_url.cmake)

add_subdirectory(three_leds)
add_subdirectory(simple-button)
add_subdirectory(simple-uart)
add_subdirectory(adc_photoresistor)
add_subdirectory(button_led_irq)
add_subdirectory(tilt_sensor_irq)
add_subdirectory(uart_tx_rx_irq)
add_subdirectory(pwm_rgb_led)
add_subdirectory(pwm_rgb_irq)
add_subdirectory(dc_motor_speed)
add_subdirectory(stepper_motor)
add_subdirectory(timer_periodic_alarm)
add_subdirectory(spi_lcd_0_96)
add_subdirectory(i2c_oled_9_6_lm75a)
add_subdirectory(multicore_temt6000_doormagnet)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )
