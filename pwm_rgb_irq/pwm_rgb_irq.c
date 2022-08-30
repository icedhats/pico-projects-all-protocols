/**
 * @file pwm_rgb_irq.c
 * @author Srinidhi Mirmira Rao
 * @brief PWM program to experiment random colours on the RGB LED using PWM wrap IRQ
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
#include "hardware/irq.h"

#define RGB_RED_PIN         18
#define RGB_GREEN_PIN       19
#define RGB_BLUE_PIN        20


void on_pwm_wrap()
{
    static int fade = 0;
    static bool going_up = true;

    //printf("Before Clear: %d\n", pwm_get_irq_status_mask());

    //pwm_clear_irq(pwm_gpio_to_slice_num(RGB_RED_PIN));
    pwm_clear_irq(pwm_gpio_to_slice_num(RGB_GREEN_PIN));

    //printf("After Clear: %d\n", pwm_get_irq_status_mask());

    if (going_up) {
        ++fade;
        if (fade > 1024) {
            fade = 1024;
            going_up = false;
        }
    } else {
        --fade;
        if (fade < 0) {
            fade = 0;
            going_up = true;
        }
    }
    // Square the fade value to make the LED's brightness appear more linear
    // Note this range matches with the wrap value
    pwm_set_gpio_level(RGB_RED_PIN, fade * fade);

}

int main()
{
    stdio_init_all();

    gpio_set_function(RGB_RED_PIN, GPIO_FUNC_PWM);
    gpio_set_function(RGB_GREEN_PIN, GPIO_FUNC_PWM);
    gpio_set_function(RGB_BLUE_PIN, GPIO_FUNC_PWM);

    uint slice_num_red = pwm_gpio_to_slice_num(RGB_RED_PIN);
    uint slice_num_green = pwm_gpio_to_slice_num(RGB_GREEN_PIN);
    uint slice_num_blue = pwm_gpio_to_slice_num(RGB_BLUE_PIN);


    // RED
    pwm_clear_irq(slice_num_red);
    pwm_set_irq_enabled(slice_num_red, true);
    irq_add_shared_handler(PWM_IRQ_WRAP, on_pwm_wrap, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
    //irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);
    pwm_init(slice_num_red, &config, true);

    // GREEN

    pwm_clear_irq(slice_num_green);
    pwm_set_enabled(slice_num_green, true);
    //irq_set_exclusive_handler(PWM_IRQ_WRAP, on_green_pwm_wrap);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    pwm_config green_config = pwm_get_default_config();
    pwm_config_set_clkdiv(&green_config, 4.f);
    pwm_init(slice_num_green, &green_config, true);

    // pwm_set_gpio_level(RGB_GREEN_PIN, 255);
    // pwm_set_enabled(slice_num_green, true);

    // pwm_set_gpio_level(RGB_BLUE_PIN, 255);
    // pwm_set_enabled(slice_num_blue, true);

    while (true)
    {
        tight_loop_contents();
    }
    return 0;
}
