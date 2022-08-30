/**
 * @file three_leds.c
 * @author Srinidhi Mirmira Rao
 * @brief Blinking 3 different LEDs 
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

#include "three_leds.h"

int main()
{
    // Create a mask based on the three LED Pins
    uint mask = 1u << LED_RED_PIN | 1u << LED_YELLOW_PIN | 1u << LED_GREEN_PIN;

    // Initializing the GPIO Pins
    gpio_init_mask(mask);

    /*
     * Case 1:
     * If you have break down gpio_init_mask() and uint mask statements then you can
     * comment out the two lines and initialize each pin at a time using gpio_init() method
    //gpio_init(LED_RED_PIN);
    //gpio_init(LED_YELLOW_PIN);
    //gpio_init(LED_GREEN_PIN);
    */

    // Setting the direction of the 3 LED pins as OUT based on the mask created above
    gpio_set_dir_out_masked(mask);

    /*
     * Case 2:
     * If you intend to use Case 1 then you can set direction of individual pins one
     * at a time using gpio_set_dir()  method
    //gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    //gpio_set_dir(LED_YELLOW_PIN, GPIO_OUT);
    //gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    */ 

    while (true) 
    {
        blink_led(LED_RED_PIN, BLINK_DELAY);
        blink_led(LED_YELLOW_PIN, BLINK_DELAY);
        blink_led(LED_GREEN_PIN, BLINK_DELAY);
    }
}

void blink_led(uint gpio_pin, int ms) 
{
    gpio_put(gpio_pin, 1);
    sleep_ms(ms);
    gpio_put(gpio_pin, 0);
    sleep_ms(ms);
}