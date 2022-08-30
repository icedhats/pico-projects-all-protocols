/**
 * @file three_leds.h
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

#ifndef _THREE_LEDS_H_
#define _THREE_LEDS_H_


#include <stdio.h>
#include "pico/stdlib.h"

#define LED_RED_PIN         16  // GP16
#define LED_YELLOW_PIN      17  // GP17
#define LED_GREEN_PIN       18  // GP18

// Delay in milli seconds
#define BLINK_DELAY         120 /*! delay in milliu seconds */


/*! \brief Blink LED based on and off based on given PIN and time delay in ms
 *
 * \param gpio_pin The LED Pin which needs to be toggled
 * \param ms Time in milli seconds between on and off
 */
void blink_led(uint gpio_pin, int ms);

#endif