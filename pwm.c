//*****************************************************************************
// FILE NAME:					pwm.c
// PROJECT:						Project04
// NAME(S):						James Pappas (jppappas)
//										Jace Hensley (jehensle)
// EMAIL(S):						James Pappas (James.Pappas@asu.edu)
//										jehensle@asu.edu
// COURSE:						CSE 325 - Embedded Microprocessor Systems
// SEMESTER:					Fall 2014
//*****************************************************************************
#include "pwm.h"
#include "global.h"
#include "gpio.h"
#include "pit.h"

void pwm_clk_config(clk_src_t clk_src, uint8 prescale, uint8 scale){
    if(clk_src == clk_SA || clk_src == clk_A){
        MCF_PWM_PWMPRCLK &= ~(0b00000111 << 0);
        MCF_PWM_PWMPRCLK |= prescale;
    }
    else if(clk_src == clk_SB || clk_src == clk_B){
        MCF_PWM_PWMPRCLK &= ~(0b000000111 << 4);
        MCF_PWM_PWMPRCLK |= (prescale << 4);
    }
    switch(clk_src){
        case clk_SA:
            MCF_PWM_PWMSCLA = scale;
            break;
        case clk_SB:
            MCF_PWM_PWMSCLB = scale;
            break;
    }
}

void pwm_chan_init(channel_t n, clk_src_t clk_src, align_t align, pwm_clock_polarity_t p_polarity){
    pwm_chan_stop(n);
    switch(n){
        case channel_2:
            gpio_port_init(gpio_port_tc, gpio_pin_1, gpio_funct_tertiary, gpio_data_dir_x, gpio_pin_state_x);
            break;
        case channel_4:
            gpio_port_init(gpio_port_tc, gpio_pin_2, gpio_funct_tertiary, gpio_data_dir_x, gpio_pin_state_x);
            break;
        case channel_5:
            gpio_port_init(gpio_port_ta, gpio_pin_2, gpio_funct_tertiary, gpio_data_dir_x, gpio_pin_state_x);
            break;
        case channel_6:
            gpio_port_init(gpio_port_tc, gpio_pin_3, gpio_funct_tertiary, gpio_data_dir_x, gpio_pin_state_x);
            break;
    }
    if(clk_src == clk_A || clk_src == clk_B){
        MCF_PWM_PWMCLK &= ~(1<<n);
    }
    else if(clk_src == clk_SA || clk_src == clk_SB){
        MCF_PWM_PWMCLK |= (1<<n);
    }
    
    if (align == align_left)
        MCF_PWM_PWMCAE &= ~(align << n);
    else
        MCF_PWM_PWMCAE |= align << n;
    
    
    
    if(p_polarity == polarity_high)
        MCF_PWM_PWMPOL |= (0x1 << n);
    else
        MCF_PWM_PWMPOL &= ~(0x1 << n);
}

void pwm_chan_start(channel_t n, uint8 period, uint8 duty){
    pwm_chan_stop(n);
    MCF_PWM_PWMPER(n) = period; 
    MCF_PWM_PWMDTY(n) = duty; 
    MCF_PWM_PWMCNT(n) = 0;
    MCF_PWM_PWME |= 0x1 << n;    
}

void pwm_chan_stop(channel_t n){
    MCF_PWM_PWME &= ~(0x1 << n);
}
