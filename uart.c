//*******************************************************************************************************
// uart.c
//
// DESCRIPTION
//
// AUTHORS
// Jace Hensley (jehensle@asu.edu)
// Computer Systems Engineering
// Arizona State University
//********************************************************************************************************

#include "uart.h"

int_isr_t g_uart_callback = 0;

void uart_init(int n, int baud_rate, int num_bits, int parity, int bits_per_char, int stop_bits, int level, int priority){
    
    gpio_port_init(gpio_port_ub, gpio_pin_0, gpio_funct_primary, gpio_data_dir_x, gpio_pin_state_x);
    gpio_port_init(gpio_port_ub, gpio_pin_1, gpio_funct_primary, gpio_data_dir_x, gpio_pin_state_x);
    gpio_port_init(gpio_port_ub, gpio_pin_2, gpio_funct_primary, gpio_data_dir_x, gpio_pin_state_x);
    gpio_port_init(gpio_port_ub, gpio_pin_3, gpio_funct_primary, gpio_data_dir_x, gpio_pin_state_x);

    MCF_UART_UCR(1) = (uint8)(0x2 << 4);
    
    MCF_UART_UCR(1) = (uint8)(0x1 << 4);
    
    MCF_UART_UCSR(1) = (uint8)(0x0d << 4);
    
    MCF_UART_UCR(1) = (uint8)(0x01 << 4);
    
    MCF_UART1_UMR = 0x13;
    
    MCF_UART1_UMR = 0x07;
    
    
    //With baud of 300 which is what we are doing
    MCF_UART_UBG1(1) |= (uint8)(0x20);
    MCF_UART_UBG2(1) |= (uint8)(0x8D);
    
    MCF_UART_UIMR(1) |=(uint8)(0x02);
    
    int_config(UART_INT_SRC(1), UART_INT_LVL(1), UART_INT_PRI(1), uart1_isr);
    int_unmask_src(UART_INT_SRC(1));
    uart_channel_disable(1);
    
    
}

void uart_channel_enable(int uart, int_isr_t callback){
    g_uart_callback = callback;
    MCF_UART_UCR(uart) &= ~(0x3); // clear the RC field
    MCF_UART_UCR(uart) |= (uint8)(0x01);
}

void uart_channel_disable(int uart) {
    MCF_UART_UCR(uart) &= ~(0x3); // clear the RC field
    MCF_UART_UCR(uart) |= (uint8)(0x2);
}

__declspec(interrupt) void uart1_isr(){
    if(g_uart_callback != 0){
        g_uart_callback();
    }
}

uint8 get_char(){
    return (uint8)MCF_UART_URB(1);
}
