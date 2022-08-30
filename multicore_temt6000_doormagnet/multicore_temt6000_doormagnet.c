/**
 * @file multicore_temt6000_doormagnet.c
 * @author Srinidhi Mirmira Rao
 * @brief Use two cores of PICO, one (Core 0) for continuously monitoring temperature using TEMT6000 sensor and
 *          use the second core (Core 1) to listen to door magnet sensor
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
#include "pico/binary_info.h"
#include "hardware/pwm.h"
#include "pico/multicore.h"
#include <math.h>

#define ADC_NUM     0
#define ADC_PIN     26
#define ADC_VREF    3.3f
#define ADC_RANGE   (1 << 12)
// 12-bit conversion, assume max value == ADC_VREF == 3.3 V
#define ADC_CONVERT (ADC_VREF / (ADC_RANGE - 1))

#define PWM_LED_PIN         15
#define LATCH_LED_PIN       17
#define LATCH_PIN           18

// https://www.i-programmer.info/programming/hardware/14849-the-pico-in-c-basic-pwm.html?start=2
uint32_t pwm_set_freq_duty(uint slice_num,
       uint chan,uint32_t f, int d)
{
    uint32_t clock = 125000000;
    uint32_t divider16 = clock / f / 4096 + 
                           (clock % (f * 4096) != 0);
    if (divider16 / 16 == 0)
    divider16 = 16;
    uint32_t wrap = clock * 16 / divider16 / f - 1;
    pwm_set_clkdiv_int_frac(slice_num, divider16/16,
                                     divider16 & 0xF);
    pwm_set_wrap(slice_num, wrap);
    pwm_set_chan_level(slice_num, chan, wrap * d / 100);
    return wrap;
}

void core1_activity()
{
    adc_init();
    adc_gpio_init(ADC_PIN);
    adc_select_input(ADC_NUM);

    gpio_set_function(PWM_LED_PIN, GPIO_FUNC_PWM);  
    uint slice_num = pwm_gpio_to_slice_num(PWM_LED_PIN);
    uint pwm_channel = pwm_gpio_to_channel(PWM_LED_PIN);
    

    uint adc_raw;
    while (true) {
        adc_raw = adc_read();
        float adc_convert = adc_raw * ADC_CONVERT;
        // printf("RAW ADC: %d\n", adc_raw);
        // printf("Converted ADC: %0.4f\n", adc_convert);
        sleep_ms(100);

        int duty_cycle = (adc_convert * 100);
        // printf("Duty Cycle: %d\n", duty_cycle);
        
        pwm_set_freq_duty(slice_num, pwm_channel, 1000 * 1000, duty_cycle);
        pwm_set_enabled(slice_num, true);
    }
}

void latch_open_callback(uint gpio, uint32_t events)
{
    printf("Inside the irq: %d\n", events);
    switch (events)
    {
    case 0x1:
        gpio_put(LATCH_LED_PIN, 1);
        break;
    case 0x2:
        gpio_put(LATCH_LED_PIN, 0);
        break;
    
    default:
        break;
    }
}

int main()
{
    stdio_init_all();

    bi_decl(bi_program_description("Read TEMT6000 on multicore program"));
    bi_decl(bi_1pin_with_name(ADC_PIN, "ADC input pin"));

    multicore_launch_core1(core1_activity);

    gpio_init(LATCH_LED_PIN);
    gpio_set_dir(LATCH_LED_PIN, GPIO_OUT);

    gpio_set_irq_enabled_with_callback(LATCH_PIN, GPIO_IRQ_LEVEL_LOW | GPIO_IRQ_LEVEL_HIGH, true, &latch_open_callback);


    while (true) 
    {
        tight_loop_contents();
        gpio_put(LATCH_LED_PIN, 1);
    }

    return 0;
}
