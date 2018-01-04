//*****************************************************************************
// FILE NAME:					pwm.h
// PROJECT:						Project04
// NAME(S):						James Pappas (jppappas)
//										Jace Hensley (jehensle)
// EMAIL(S):						James Pappas (James.Pappas@asu.edu)
//										jehensle@asu.edu
// COURSE:						CSE 325 - Embedded Microprocessor Systems
// SEMESTER:					Fall 2014
//*****************************************************************************
#include "global.h"
#include "gpio.h"

#ifndef PWM_H_
#define PWM_H_

typedef enum{
    clk_A = 0,
    clk_B = 1,
    clk_SA = 2,
    clk_SB = 3
}clk_src_t;

typedef enum{
    align_left = 0,
    align_center = 1
}align_t;

typedef enum{
    channel_2 = 2,
    channel_4 = 4,
    channel_5 = 5,
    channel_6 = 6
}channel_t;

typedef enum {
    polarity_low = 0,
    polarity_high = 1    
}pwm_clock_polarity_t;

void pwm_chan_init(channel_t n, clk_src_t clk_src, align_t align, pwm_clock_polarity_t p_polarity);

void pwm_clk_config(clk_src_t, uint8, uint8);

void pwm_chan_start(channel_t, uint8, uint8);

void pwm_chan_stop(channel_t);





#endif /* PWM_H_ */
