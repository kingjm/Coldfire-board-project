//*****************************************************************************
// FILE NAME:					oct_rgb_led.h
// PROJECT:						Project04
// NAME(S):						James Pappas (jppappas)
//										Jace Hensley (jehensle)
// EMAIL(S):						James Pappas (James.Pappas@asu.edu)
//										jehensle@asu.edu
// COURSE:						CSE 325 - Embedded Microprocessor Systems
// SEMESTER:					Fall 2014
//*****************************************************************************
#include "global.h"

#ifndef OCT_RGB_LED_H_
#define OCT_RGB_LED_H_


typedef enum{
    oct_rgb_led_1 = 4,
    oct_rgb_led_2 = 6,
    oct_rgb_led_3 = 7
}oct_rgb_led_t;

typedef enum {
    oct_rgb_led_state_off = 0,
    oct_rgb_led_state_on = 1
} oct_rgb_led_state_t;

typedef enum{
    oct_rgb_led_color_red = 0,
    oct_rgb_led_color_orange = 1,
    oct_rgb_led_color_yellow = 2,
    oct_rgb_led_color_green = 3,
    oct_rgb_led_color_indigo = 4,
    oct_rgb_led_color_blue = 5,
    oct_rgb_led_color_violet = 6,
    oct_rgb_led_color_white = 7
}oct_rgb_led_color_t;

typedef enum{
    rgb_led_1_com = 0,
    rgb_led_2_com = 1,
    rgb_led_3_com = 2
}oct_rgb_led_com_t;



void oct_rgb_led_all_off();
void oct_rgb_led_all_on();
void oct_rgb_led_init();
void oct_rgb_led_off(int p_led);
void oct_rgb_led_on(int p_led);
void oct_rgb_led_set_color(int p_led, oct_rgb_led_color_t p_color);
void oct_rgb_led_toggle(int p_led);
static void oct_rgb_led_callback();


#endif /* OCT_RGB_LED_H_ */
