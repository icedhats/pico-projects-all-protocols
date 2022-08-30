/**
 * @file pwm_rgb_led.c
 * @author Srinidhi Mirmira Rao
 * @brief PWM program to experiment random colours on the RGB LED without using PWM wrap IRQ
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
#include "hardware/pwm.h"

#define RGB_RED_PIN         18
#define RGB_GREEN_PIN       19
#define RGB_BLUE_PIN        20

int main()
{
    stdio_init_all();
    gpio_set_function(RGB_RED_PIN, GPIO_FUNC_PWM);
    gpio_set_function(RGB_GREEN_PIN, GPIO_FUNC_PWM);
    gpio_set_function(RGB_BLUE_PIN, GPIO_FUNC_PWM);

    uint slice_num_red = pwm_gpio_to_slice_num(RGB_RED_PIN);
    uint slice_num_green = pwm_gpio_to_slice_num(RGB_GREEN_PIN);
    uint slice_num_blue = pwm_gpio_to_slice_num(RGB_BLUE_PIN);

    uint channel_num_red = pwm_gpio_to_channel(RGB_RED_PIN);
    uint channel_num_green = pwm_gpio_to_channel(RGB_GREEN_PIN);
    uint channel_num_blue = pwm_gpio_to_channel(RGB_BLUE_PIN);

    printf("RED Slice: %d\t Channel: %d\n", slice_num_red, channel_num_red);
    printf("GREEN Slice: %d\t Channel: %d\n", slice_num_green, channel_num_green);
    printf("BLUE Slice: %d\t Channel: %d\n", slice_num_blue, channel_num_blue);
    

    while (true)
    {
        for (uint16_t i = 1; i < 2056; i++) {
            for (uint16_t j = 2056; j >=1 ; j--) {
                pwm_set_wrap(slice_num_red, i);
                pwm_set_chan_level(slice_num_red, channel_num_red, j);
                //pwm_set_chan_level(slice_num_red, PWM_CHAN_A, 1024);
                pwm_set_enabled(slice_num_red, true);

                pwm_set_wrap(slice_num_green, i);
                //pwm_set_chan_level(slice_num_green, PWM_CHAN_B, j);
                pwm_set_chan_level(slice_num_green, channel_num_green, 1024);
                pwm_set_enabled(slice_num_green, true);

                pwm_set_wrap(slice_num_blue, j);
                pwm_set_chan_level(slice_num_blue, channel_num_blue, i);
                //pwm_set_chan_level(slice_num_blue, PWM_CHAN_A, 1560);
                pwm_set_enabled(slice_num_blue, true);  
            }
            
        }
    }
    return 0;
}
