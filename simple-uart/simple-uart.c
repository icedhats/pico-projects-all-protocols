/**
 * @file simple-uart.c
 * @author Srinidhi Mirmira Rao
 * @brief Log using Logger library for PICO without using IRQs and printf
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

#include <stdio.h>
#include "pico/stdlib.h"
#include "logger_uart_blocking.h"


#define UART_ID     uart0
#define BAUD_RATE   115200

#define UART_TX_PIN 0   // GP0
#define UART_RX_PIN 1   // GP1

int main()
{
    // This function is from logger_uart_blocking lib
    init_uart(UART_ID, BAUD_RATE, UART_TX_PIN, UART_RX_PIN, true);

    while (true)
    {
        log_string_with_check(UART_ID, "Checking......");
        sleep_ms(1000);
        log_string_without_check(UART_ID, "This is from RPi PICO 2040\n");
        sleep_ms(1000);
    }

    return 0;
}
