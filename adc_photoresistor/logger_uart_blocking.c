/**
 * @file logger_uart_blocking.c
 * @author Srinidhi Mirmira Rao
 * @brief Logger library for PICO without using IRQs and printf
 * @version 0.1
 * @date 2022-08-28
 * 
 * @copyright 
 * MIT License
 *
 * Copyright (c) 2022 Srinidhi Mirmira Rao
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

#include "logger_uart_blocking.h"

uint init_uart(uart_inst_t *uart_id, uint baudrate, uint tx_pin, uint rx_pin, bool log_info)
{
    // uart_init initializes the UART for the given UART ID and Baudrate
    uint baud_rate_after_init = uart_init(uart_id, baudrate);

    // gpio_set_function function sets the given GPIO PIN, in our case 
    // TX and RX pin, to their respective functions mentioned in the
    // second param
    gpio_set_function(tx_pin, GPIO_FUNC_UART);
    gpio_set_function(rx_pin, GPIO_FUNC_UART);

    if (log_info == true)
    {
        uart_puts(uart_id, "\n\n*** Starting the UART Communication with Baud rate: ");
        char str[32]; // We need at least 9 to store the baudrate.
        sprintf(str, "%u ***\n\n", baud_rate_after_init);
        uart_puts(uart_id, str);
    }  
    return baud_rate_after_init;
}

bool log_string_with_check(uart_inst_t *uart_id, char *str_data)
{
    // Check if the UART is enabled on the UART ID
    if (uart_is_enabled(uart_id) == true) 
    {
        uart_puts(uart_id, str_data);
        // The true does not signify a successfull write rather 
        // the state of the UART
        return true;
    }
    return false;
}

void log_string_without_check(uart_inst_t *uart_id, char *str_data)
{
    uart_puts(uart_id, str_data);
}