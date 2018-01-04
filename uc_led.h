//*****************************************************************************
// uc_led.h
//
// DESCRIPTION:
//
// AUTHOR(S):
// James Pappas (James.Pappas@asu.edu)
// ID# 1204791792
// Computer Systems Engineering
// Arizona State University
//*****************************************************************************
#ifndef UC_LED_H_
#define UC_LED_H_

#include "support_common.h"

typedef enum { 
 uc_led_1 = 1, // Represents LED1
 uc_led_2 = 2, // Represents LED2
 uc_led_3 = 3, // Represents LED3
 uc_led_4 = 4 // Represents LED4
} uc_led_t;

void uc_led_all_off();

void uc_led_all_on();

void uc_led_init();

void uc_led_off(int p_led);

void uc_led_on(int p_led);

void uc_led_toggle(int p_led);

#endif /* UC_LED_H_ */
