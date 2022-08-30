# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(uart_tx_rx_irq C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(uart_tx_rx_irq uart_tx_rx_irq.c )

pico_set_program_name(uart_tx_rx_irq "uart_tx_rx_irq")
pico_set_program_version(uart_tx_rx_irq "0.1")

pico_enable_stdio_uart(uart_tx_rx_irq 1)
pico_enable_stdio_usb(uart_tx_rx_irq 0)

# Add the standard library to the build
target_link_libraries(uart_tx_rx_irq pico_stdlib)

pico_add_extra_outputs(uart_tx_rx_irq)

