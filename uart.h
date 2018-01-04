//*******************************************************************************************************
// uart.h
//
// DESCRIPTION
//
// AUTHORS
// Jace Hensley (jehensle@asu.edu)
// Computer Systems Engineering
// Arizona State University
//********************************************************************************************************

#ifndef UART_H_
#define UART_H_

#include "gpio.h"
#include "int.h"
#include "global.h"

void uart_init(int n, int baud_rate, int num_bits, int parity, int bits_per_char, int stop_bits, int level, int priority);
void uart_channel_enable(int uart, int_isr_t callback);
void uart_channel_disable(int uart);
__declspec(interrupt) void uart1_isr();
uint8 get_char();

#endif

