/**
 * @file logger_uart_blocking.h
 * @author Srinidhi Mirmira Rao
 * @brief Logger library for PICO without using IRQs and printf
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

#ifndef _LOGGER_UART_BLOCKING_H_
#define _LOGGER_UART_BLOCKING_H_

#include <stdio.h>
#include "pico/stdlib.h"

/*! \brief Initiates UART by setting the baud, tx and rx pin.
 *          This method can be used to log the baud rate once the UART is 
 *          is successfully initiated.
 *
 * \param uart_id Pointer to UART ID, either 0 or 1
 * \param baudrate Baudrate for the serial port (hz)
 * \param tx_pin GPIO Pin that needs to be used as transmission (TX)
 * \param rx_pin GPIO Pin that needs to be used as reception (RX)
 * \param log_info Set this true if baud rate needs to be logged after a successfull 
 *                  initialization
 * \return The baud rate returned by the uart lib
 */
uint init_uart(uart_inst_t *uart_id, uint baudrate, uint tx_pin, uint rx_pin, bool log_info);

/*! \brief Transmits string after checking if UART is enabled or not
 *
 * \param uart_id Pointer to UART ID, either 0 or 1
 * \param str_data String that needs to be transmitted over UART
 * \return The state of UART for the given UART ID
 */
bool log_string_with_check(uart_inst_t *uart_id, char *str_data);

/*! \brief Transmits string without checking if UART is enabled or not
 *
 * \param uart_id Pointer to UART ID, either 0 or 1
 * \param str_data String that needs to be transmitted over UART
 */
void log_string_without_check(uart_inst_t *uart_id, char *str_data);

#endif