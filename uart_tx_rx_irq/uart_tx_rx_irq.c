/**
 * @file uart_tx_rx_irq.c
 * @author Srinidhi Mirmira Rao
 * @brief Program to show problems with UART IRQ
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
#include <string.h>
#include <stdlib.h>

#define UART_ID     uart0
#define BAUD_RATE   115200
#define DATA_BITS   8
#define STOP_BITS   1
#define PARITY      UART_PARITY_NONE

#define UART0_TX_PIN    0
#define UART0_RX_PIN    1

void on_uart_xx()
{
    /**
     * If we enable TX interrupt then the irq gets called continuously as it keeps looking
     * for data to be written and does not even try to read from the RX line.  Try uncommenting
     * the next three lines and check that "UART Started" never gets written because as soon 
     * as the MCU get IRQ enabled for TX, it gets triggered.  To see "UART Started" enable the 
     * IRQ after calling the uart_puts in the main method.  The "UART Started" gets transmitted
     * but MCU TX line will be hungry to write again and keeps triggering the IRQ.
     * 
     */
    // while (uart_is_writable) {
    //     gpio_put(25, 1);
    //     uart_putc(UART_ID, 'a');
    // }

    while (uart_is_readable(UART_ID)) {
        /**
         * You can observe a faintest glow in the LED every time
         * you type in a character.
         */
        gpio_put(25, 1);
        uint8_t ch = uart_getc(UART_ID);
        // Can we send it back?
        if (uart_is_writable(UART_ID)) {
            uart_putc(UART_ID, ch);
        }
    }
    // gpio_put(25, 0);
}

int main()
{
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    int __unused actual_baudrate = uart_init(UART_ID, BAUD_RATE);

    gpio_set_function(UART0_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART0_RX_PIN, GPIO_FUNC_UART);

    uart_set_hw_flow(UART_ID, false, false);

    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    uart_set_fifo_enabled(UART_ID, false);

    irq_set_exclusive_handler(UART0_IRQ, on_uart_xx);
    irq_set_enabled(UART0_IRQ, true);

    uart_puts(UART_ID, "\nUART Started\n");

    /**
     * To enable the TX IRQ send in true for the 3rd parameter.
     * Observe that MCU's TX line is always looking for something
     * to write since the FIFO queue for TX is empty so, the IRQ
     * for TX gets triggered continuously.
     */
    uart_set_irq_enables(UART_ID, true, false);

    while(1)
    {
        gpio_put(25, 0);
    }  

    return 0;
}
