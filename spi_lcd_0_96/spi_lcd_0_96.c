/**
 * @file spi_lcd_0_96.c
 * @author Srinidhi Mirmira Rao
 * @brief Display on 0.96 inch LCD with SPI using the lib from Waveshare
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
#include "LCD_0in96.h"
#include "GUI_Paint.h"
#include "ImageData.h"
#include "hardware/adc.h"

#define TEMPERATURE_UNITS 'C'

uint pwm_slice_num_bl_pin;

void set_pwm_bl(uint8_t value)
{
    if (value < 0 || value > 100) {
        printf("ERROR: set_pwm_bl, for value: %d", value);
    } else {
        pwm_set_chan_level(pwm_slice_num_bl_pin, PWM_CHAN_B, value);
    }
}

void init_onboard_temperature()
{
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
}

/* References for this implementation:
 * raspberry-pi-pico-c-sdk.pdf, Section '4.1.1. hardware_adc'
 * pico-examples/adc/adc_console/adc_console.c */
float read_onboard_temperature(const char unit) {
    
    /* 12-bit conversion, assume max value == ADC_VREF == 3.3 V */
    const float conversionFactor = 3.3f / (1 << 12);

    float adc = (float)adc_read() * conversionFactor;
    float tempC = 27.0f - (adc - 0.706f) / 0.001721f;

    if (unit == 'C') {
        return tempC;
    } else if (unit == 'F') {
        return tempC * 9 / 5 + 32;
    }

    return -1.0f;
}

int main()
{
    stdio_init_all();

    init_onboard_temperature();

    // Initializing the SPI PINS
    spi_init(spi1, 10000 * 1000); // 10Mhz
    gpio_set_function(LCD_CLK_PIN, GPIO_FUNC_SPI);  // SCK Pin of SPI
    gpio_set_function(LCD_MOSI_PIN, GPIO_FUNC_SPI); // MOSI Pin of SPI

    // LCD Data/Command Control PIN (High: Data, Low: Command)
    gpio_init(LCD_DC_PIN);
    gpio_set_dir(LCD_DC_PIN, GPIO_OUT);

    // LCD Chip Select PIN, low active
    gpio_init(LCD_CS_PIN);
    gpio_set_dir(LCD_CS_PIN, GPIO_OUT);

    // LCD Reset Pin, low active
    gpio_init(LCD_RST_PIN);
    gpio_set_dir(LCD_RST_PIN, GPIO_OUT);

    // LCD Backlight Control
    gpio_init(LCD_BL_PIN);
    gpio_set_dir(LCD_BL_PIN, GPIO_OUT);

    // Not Selecting the LCD now
    gpio_put(LCD_CS_PIN, 1);
    // Put the DC line in command mode
    gpio_put(LCD_DC_PIN, 0);
    // Switch on the backlight
    gpio_put(LCD_BL_PIN, 1);

    // PWM Configuration for the backlight 
    gpio_set_function(LCD_BL_PIN, GPIO_FUNC_PWM);
    pwm_slice_num_bl_pin = pwm_gpio_to_slice_num(LCD_BL_PIN);
    pwm_set_wrap(pwm_slice_num_bl_pin, 100);
    pwm_set_chan_level(pwm_slice_num_bl_pin, PWM_CHAN_B, 1);
    pwm_set_clkdiv(pwm_slice_num_bl_pin, 50);
    pwm_set_enabled(pwm_slice_num_bl_pin, true);

    // Initializing the LCD
    LCD_0IN96_Init(HORIZONTAL);
    LCD_0IN96_Clear(WHITE);
    sleep_ms(1000);

    UDOUBLE Imagesize = LCD_0IN96_HEIGHT*LCD_0IN96_WIDTH*2;
    UWORD *BlackImage;
    if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }
    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage((UBYTE *)BlackImage,LCD_0IN96.WIDTH,LCD_0IN96.HEIGHT, 0, WHITE);
    Paint_SetScale(65);
    Paint_Clear(WHITE);
    Paint_SetRotate(ROTATE_0);
    Paint_Clear(WHITE);
    // https://stackoverflow.com/questions/19008733/storing-rgb-in-an-unsigned-16bit-integer
    //uint16_t foreground_color = ((235 << 12) | (64 << 5) | (52));

    Paint_DrawImage(gImage_0inch96_1,0,0,160,80);
    LCD_0IN96_Display(BlackImage);
    sleep_ms(1000);

    while (true)
    {
        float temperature = read_onboard_temperature(TEMPERATURE_UNITS);
        Paint_DrawString_EN(1, 1, "Temperature: ", &Font12, 0xfff0, 0x000f);
        Paint_DrawNum(84, 1, temperature, &Font12, 2, 0x0000, 0xfee0);
        Paint_DrawCircle( 124, 4, 2, RED, DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
        Paint_DrawString_EN(128, 1, "C", &Font12, 0xfff0, 0x000f);
        Paint_DrawLine(1, 13, LCD_0IN96_WIDTH, 13, BLACK, 1, LINE_STYLE_SOLID);

        
        LCD_0IN96_Display(BlackImage);
        sleep_ms(1000);
        
    }

    return 0;
}
