/**
 * @file i2c_oled_9_6_lm75a.cpp
 * @author Srinidhi Mirmira Rao
 * @brief Display temperature on a 0.96 inches OLED connected via i2c using LM75a sensor 
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
#include "pico-ss-oled/include/ss_oled.hpp"
#include "M2M_LM75A.h"

// https://github.com/martinkooij/pi-pico-ss-oled
// RPI Pico
#define SDA_PIN 4
#define SCL_PIN 5
#define PICO_I2C i2c0
#define I2C_SPEED 400 * 1000


#define OLED_WIDTH 128
#define OLED_HEIGHT 32

int main()
{
    stdio_init_all();

    static uint8_t ucBuffer[1024];
uint8_t uc[8];
int i, j, rc;
char szTemp[32];
picoSSOLED myOled(OLED_128x32, 0x3c, 0, 0, PICO_I2C, SDA_PIN, SCL_PIN, I2C_SPEED);
    
  rc = myOled.init() ;
  myOled.set_back_buffer(ucBuffer);
  M2M_LM75A lm75a;
  lm75a.shutdown();
  sleep_ms(1000);
  
  while (1) {
    lm75a.wakeup();
    sleep_ms(100);
    float temperature = lm75a.getTemperature();
    printf("Temperature: %f\n", temperature);
    sleep_ms(3000);

    char buffer[64];
    int ret = snprintf(buffer, sizeof buffer, "%f", temperature);
    if (rc != OLED_NOT_FOUND)
    {   
      myOled.fill(0,1);
      myOled.set_contrast(127);
      myOled.write_string(0,0,0,(char *)"Temperature ", FONT_8x8, 0, 1);
      myOled.write_string(0,4,1,buffer, FONT_8x8, 0, 1);
    }
    lm75a.shutdown();
    sleep_ms(100);
  }


  return 0;
}
