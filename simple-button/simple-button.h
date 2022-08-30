#ifndef _SIMPLE_BUTTON_H_
#define _SIMPLE_BUTTON_H_


#include <stdio.h>
#include "pico/stdlib.h"


#define BUTTON_PIN          15  // GP15
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