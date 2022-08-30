/**
 * @file stepper_motor.c
 * @author Srinidhi Mirmira Rao
 * @brief Stepper motor interface using uln2003
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

#define STEPPER_MOTOR_IN1_PIN       16
#define STEPPER_MOTOR_IN2_PIN       17
#define STEPPER_MOTOR_IN3_PIN       18
#define STEPPER_MOTOR_IN4_PIN       19

#define MICRO_SEC_DELAY     10000
#define NUMBER_OF_STEPS_FOR_ONE_REVOLUTION  2038

// https://lastminuteengineers.com/28byj48-stepper-motor-arduino-tutorial/
// https://peppe8o.com/stepper-motor-with-raspberry-pi-pico-28byj-48-and-uln2003-wiring-and-micropython-code/
// https://github.com/arduino-libraries/Stepper/blob/master/src/Stepper.cpp

const uint stepper_sequence[8][4] = {
    {0, 0, 0, 1},
    {0, 0, 1, 1},
    {0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 1, 0, 0},
    {1, 1, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 1}
};

// Code Optimization
// Create an enum for forward and backward rotation
// Create a single function for movements

void move_forward(uint delay, uint rotations)
{
    int total_count = rotations * NUMBER_OF_STEPS_FOR_ONE_REVOLUTION;
    printf("Forward: %d\n", total_count);
    while (total_count >= 0)
    {
        printf("Forward Step: %d\n", total_count);
        for (int i = 0; i < 8; i++) {
            gpio_put(STEPPER_MOTOR_IN1_PIN, stepper_sequence[i][0]);
            gpio_put(STEPPER_MOTOR_IN2_PIN, stepper_sequence[i][1]);
            gpio_put(STEPPER_MOTOR_IN3_PIN, stepper_sequence[i][2]);
            gpio_put(STEPPER_MOTOR_IN4_PIN, stepper_sequence[i][3]);

            sleep_us(delay);
            total_count--;
        }
    
    }
    
}

void move_backward(uint delay, uint rotations)
{
    int total_count = rotations * NUMBER_OF_STEPS_FOR_ONE_REVOLUTION;
    printf("%d\n", total_count);
    while (total_count >= 0)
    {
        printf("%d\n", total_count);
        for (int i = 7; i >= 0; i--) {
            gpio_put(STEPPER_MOTOR_IN1_PIN, stepper_sequence[i][0]);
            gpio_put(STEPPER_MOTOR_IN2_PIN, stepper_sequence[i][1]);
            gpio_put(STEPPER_MOTOR_IN3_PIN, stepper_sequence[i][2]);
            gpio_put(STEPPER_MOTOR_IN4_PIN, stepper_sequence[i][3]);

            sleep_us(delay);
            total_count--;
        }
    }
}

uint calculate_delay_for_speed(uint8_t speed)
{
    return 60L * 1000L * 1000L / NUMBER_OF_STEPS_FOR_ONE_REVOLUTION / speed;
}

int main()
{
    stdio_init_all();

    uint pin_mask = 1u << STEPPER_MOTOR_IN1_PIN | 1u << STEPPER_MOTOR_IN2_PIN | 1u << STEPPER_MOTOR_IN3_PIN | 1u << STEPPER_MOTOR_IN4_PIN;
    
    gpio_init_mask(pin_mask);
    gpio_set_function(STEPPER_MOTOR_IN1_PIN, GPIO_FUNC_SIO);
    gpio_set_function(STEPPER_MOTOR_IN2_PIN, GPIO_FUNC_SIO);
    gpio_set_function(STEPPER_MOTOR_IN3_PIN, GPIO_FUNC_SIO);
    gpio_set_function(STEPPER_MOTOR_IN4_PIN, GPIO_FUNC_SIO);
    gpio_set_dir_out_masked(pin_mask);
    
    int count = 0;

    while (true)
    {
        count = calculate_delay_for_speed(20);
        move_forward(count, 1);
        sleep_ms(3000);
        move_backward(count, 2);
        sleep_ms(3000);
    }


    return 0;
}
