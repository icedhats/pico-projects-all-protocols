/**
 * @file button_led_irq.c
 * @author Srinidhi Mirmira Rao
 * @brief Program to switch on & off LED using an interrupt when a button is pressed
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

#define BUTTON_PIN      15          // GP15 as input for button
#define LED_YELLOW_PIN  16          // GP16

#define UART_ID     uart0           // Choosing UART0 as the UART channel
#define BAUD_RATE   115200          // Baud rate (in Hz)

#define UART_TX_PIN 0               // GP0 as UART0 TX
#define UART_RX_PIN 1               // GP1 as UART1 RX


/*! \brief Callback function for the button press interrupt
 *
 * \param gpio The pin on which the interrupt was triggered
 * \param event_mask The type of event which triggered the interrupt 
 */
void button_irq_callback(uint gpio, uint32_t event_mask)
{
    bool current_level = gpio_get_out_level(LED_YELLOW_PIN);    // Get the current state of LED, whether it is on or off

    gpio_put(LED_YELLOW_PIN, !current_level);                   // Take the current_level, and send its negation as output

    // The value associated with each event type.  Check pico_sdk header doc for a better explanation.
    // GPIO_IRQ_LEVEL_LOW = 0x1u,
    // GPIO_IRQ_LEVEL_HIGH = 0x2u,
    // GPIO_IRQ_EDGE_FALL = 0x4u,
    // GPIO_IRQ_EDGE_RISE = 0x8u,
    switch (event_mask)
    {
        case 12u:                                               // GPIO_IRQ_EDGE_FALL + GPIO_IRQ_EDGE_RISE yields 12 (base 10)
        log_string_without_check(UART_ID, "GPIO_IRQ_EDGE_FALL && GPIO_IRQ_EDGE_RISE\n");
        break;
        case 0x4u:                                              
        log_string_without_check(UART_ID, "GPIO_IRQ_EDGE_FALL\n");
        break;
        case 0x8u:
        log_string_without_check(UART_ID, "GPIO_IRQ_EDGE_RISE\n");
        break;
    
    default:
        break;
    }

    // The next three lines converts the event id to string
    // and logs them using the UART
    char event_str[32];
    sprintf(event_str, "%d", event_mask);
    log_string_without_check(UART_ID, event_str);
    
}

int main()
{
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_irq_callback);     // setting up the interrupt with callback enabled and enabling the interrupt

    gpio_init(LED_YELLOW_PIN);                  // Initializing the LED pin
    gpio_set_dir(LED_YELLOW_PIN, GPIO_OUT);     // Setting the direction of LED pin as output

    init_uart(UART_ID, BAUD_RATE, UART_TX_PIN, UART_RX_PIN, true);      // Initializing UART using logger_uart_blocking

    while(true);            // Don't let the MCU return from main function

    return 0;
}


