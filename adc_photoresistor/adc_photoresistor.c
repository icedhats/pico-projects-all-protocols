/**
 * @file adc_photoresistor.c
 * @author Srinidhi Mirmira Rao
 * @brief Reading LDR using ADC 
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
#include "hardware/adc.h"
#include "logger_uart_blocking.h"

#define ADC0_ID      0          // Choosing ADC0 as the adc input channel
#define ADC0_PIN    26          // GP26 corresponds to ADC0

#define UART_ID     uart0       // Choosing UART0 as the UART channel
#define BAUD_RATE   115200      // Baud rate (in Hz)

#define UART_TX_PIN 0           // GP0 as UART0 TX
#define UART_RX_PIN 1           // GP1 as UART1 RX

#define LED_RED_PIN         16  // GP16
#define LED_YELLOW_PIN      17  // GP17
#define LED_GREEN_PIN       18  // GP18

int main()
{
    adc_init();                 // Initializing the ADC hardware
    adc_gpio_init(ADC0_PIN);    // Initializing the GPIO PIN as ADC Input
    adc_select_input(ADC0_ID);  // Choosing ADC0 as the ADC input

    init_uart(UART_ID, BAUD_RATE, UART_TX_PIN, UART_RX_PIN, true);  // Initializing UART using logger_uart_blocking
    
    uint mask = 1u << LED_RED_PIN | 1u << LED_YELLOW_PIN | 1u << LED_GREEN_PIN;     // Create a mask based on the three LED Pins
    gpio_init_mask(mask);           // Initializing the GPIO Pins for LEDs
    gpio_set_dir_out_masked(mask);  // Setting the direction of the 3 LED pins as OUT based on the mask created above

    uint16_t result = 0;            // Variable for storing ADC reads from LDR
    char str_result[32];            // char[] required to store the result in string format

    while (true) {
        result = adc_read();        // Reads ADC with single sampling
                                    // 900(total darkness with fingers covering LED)
                                    // 4095(Mobile torch directly pointed on LDR) 
                                    // was the reading for my room lighting conditions

        sprintf(str_result, "%u\n\n", result);
        log_string_without_check(UART_ID, str_result);

        if (result < 3000 && result >= 2400) {
            gpio_put(LED_RED_PIN, 1);
        } else if (result < 2400 && result >= 1800) {
            gpio_put(LED_RED_PIN, 1);
            gpio_put(LED_YELLOW_PIN, 1);
        } else if (result < 1800) {
            gpio_put(LED_RED_PIN, 1);
            gpio_put(LED_YELLOW_PIN, 1);
            gpio_put(LED_GREEN_PIN, 1);
        } else {
            gpio_put(LED_RED_PIN, 0);
            gpio_put(LED_YELLOW_PIN, 0);
            gpio_put(LED_GREEN_PIN, 0);
        }
        sleep_ms(500);
    }

    return 0;
}
