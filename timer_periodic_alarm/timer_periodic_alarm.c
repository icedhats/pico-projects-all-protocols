/**
 * @file timer_periodic_alarm.c
 * @author Srinidhi Mirmira Rao
 * @brief Program to show problems with single core with multiple IRQs  
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

#include "timer_periodic_alarm.h"

#define LED_RED_PIN         18
#define LED_YELLOW_PIN      19
#define LED_GREEN_PIN       20
#define LED_BLUE_PIN        15
#define BUZZER_PIN          13
#define PIR_MOTION_PIN      21


int64_t buzzer_alarm(alarm_id_t id, void *user_data)
{
    printf("Inside buzzer_alarm_on");
    gpio_put(BUZZER_PIN, 1);
    busy_wait_ms(2000);
    gpio_put(BUZZER_PIN, 0);
}

bool one_second_timer(struct repeating_timer *rt)
{
    printf("Inside one_second_timer");
    gpio_put(LED_BLUE_PIN, 1);
    busy_wait_ms(500);
    gpio_put(LED_BLUE_PIN, 0);
    return true;
}

void motion_detected_irq(uint gpio, uint32_t events) {

    switch (events)
    {
        case 0x4u:      
        gpio_put(LED_RED_PIN, 0);                                        
        printf("GPIO_IRQ_EDGE_FALL\n");
        break;
        case 0x8u:
        gpio_put(LED_RED_PIN, 1);
        printf("GPIO_IRQ_EDGE_RISE\n");
        break;
    
    default:
        break;
    }
    
}

void motion_stopped_irq(uint gpio, uint32_t events) {
    printf("motion_stopped_irq\n");
    gpio_put(LED_RED_PIN, 0);
}

int main()
{
    stdio_init_all();

    uint mask_output_pins = 1u << LED_RED_PIN | 1u << LED_YELLOW_PIN | 1u << LED_GREEN_PIN;
    mask_output_pins |= 1u << LED_BLUE_PIN;
    mask_output_pins |= 1u << BUZZER_PIN;

    gpio_init_mask(mask_output_pins);
    gpio_set_dir_out_masked(mask_output_pins);

    gpio_set_irq_enabled_with_callback(PIR_MOTION_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &motion_detected_irq);

    add_alarm_in_ms(10000, buzzer_alarm, NULL, false);

    struct repeating_timer blue_timer;
    add_repeating_timer_ms(500, one_second_timer, NULL, &blue_timer);

    while (true) 
    {
        tight_loop_contents();
    }

    return 0;
}
