/**
 * @file tilt_sensor_irq.c
 * @author Srinidhi Mirmira Rao
 * @brief Reading a SW520D Tilt Sensor using a IRQ
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
#include "hardware/gpio.h"
#include "logger_uart_blocking.h"

#define LED_YELLOW_PIN  16              // GP16
#define TILT_SENSOR_PIN 18              // GP18 SW520D Tilt Sensor

#define UART_ID     uart0               // Choosing UART0 as the UART channel
#define BAUD_RATE   115200              // Baud rate (in Hz)

#define UART_TX_PIN 0                   // GP0 as UART0 TX
#define UART_RX_PIN 1                   // GP1 as UART1 RX


/*! \brief Callback function for the tilt movement
 *         In this callback, the current event which triggered the interrupt needs to be disabled immediately
 *          as the tilt sensor will trigger multiple interrupt for the same event.   Therefore, once the interrupt
 *          for the event high is triggered then high event interrupt is diabled and the interrupt is set for low event
 *          with the same callback function.  The principle holds good once the low event interrupt is triggered.
 *
 * \param gpio The pin on which the interrupt was triggered
 * \param event_mask The type of event which triggered the interrupt 
 */
void tilt_sensor_callback(uint gpio, uint32_t event_mask)
{
    // Check to see if the event is GPIO_IRQ_LEVEL_LOW
    if (event_mask == 0x1u) {
        gpio_set_irq_enabled(TILT_SENSOR_PIN, GPIO_IRQ_LEVEL_LOW, false);           // Disable GPIO_IRQ_LEVEL_LOW interrupt
        gpio_set_irq_enabled_with_callback(TILT_SENSOR_PIN, GPIO_IRQ_LEVEL_HIGH, true, &tilt_sensor_callback);  // Enable the same callback for GPIO_IRQ_LEVEL_HIGH interrupt

        gpio_put(LED_YELLOW_PIN, 1);    // Output high to switch on the LED
    } else if (event_mask == 0x2u) {    //Check to see if the event is GPIO_IRQ_LEVEL_HIGH 
        gpio_set_irq_enabled(TILT_SENSOR_PIN, GPIO_IRQ_LEVEL_HIGH, false);          // Disable GPIO_IRQ_LEVEL_HIGH interrupt
        gpio_set_irq_enabled_with_callback(TILT_SENSOR_PIN, GPIO_IRQ_LEVEL_LOW, true, &tilt_sensor_callback);   // Enable the same callback for GPIO_IRQ_LEVEL_LOW interrupt

        gpio_put(LED_YELLOW_PIN, 0);    // Output low to switch off the LED
    }
}

int main()
{
    gpio_set_irq_enabled_with_callback(TILT_SENSOR_PIN, GPIO_IRQ_LEVEL_HIGH, true, &tilt_sensor_callback);      // Enable the same callback for GPIO_IRQ_LEVEL_HIGH interrupt

    gpio_init(LED_YELLOW_PIN);                  // Initializing the LED pin
    gpio_set_dir(LED_YELLOW_PIN, GPIO_OUT);     // Setting the direction of LED pin as output

    init_uart(UART_ID, BAUD_RATE, UART_TX_PIN, UART_RX_PIN, true);      // Initializing UART using logger_uart_blocking

    while(true);            // Don't let the MCU return from main function

    return 0;
}
