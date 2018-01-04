//**************************************************************************************************************
// FILE NAME:               uc_dipsw.c
// PROJECT:                     Project04
// NAME(S):                     James Pappas (jppappas)
//                                      Jace Hensley (jehensle)
// EMAIL(S):                        James Pappas (James.Pappas@asu.edu)
//                                      jehensle@asu.edu
// COURSE:                      CSE 325 - Embedded Microprocessor Systems
// SEMESTER:                    Fall 2014
//*****************************************************************************
#include "uc_dipsw.h"
#include "gpio.h"

// Calls gpio_port_get_pin_state() to return the state of the pin connected to subswitch p_switch.
uc_dipsw_state_t uc_dipsw_get_state(uc_dipsw_t p_switch) {
    // uc_dipsw_state_t state = gpio_port_get_pin_state(gpio_port_dd, p_switch);
    return (uc_dipsw_state_t)(gpio_port_get_pin_state(gpio_port_dd, (gpio_pin_t)p_switch));   
}

// Calls gpio_port_init() to initialize port DD so we can use subswitches 1, 2, 3, and 4.
void uc_dipsw_init() {
    gpio_port_init(gpio_port_dd, (gpio_pin_t)uc_dipsw_1, gpio_funct_gpio, gpio_data_dir_in, (gpio_pin_state_t)uc_dipsw_state_on);
    gpio_port_init(gpio_port_dd, (gpio_pin_t)uc_dipsw_2, gpio_funct_gpio, gpio_data_dir_in, (gpio_pin_state_t)uc_dipsw_state_on);
    gpio_port_init(gpio_port_dd, (gpio_pin_t)uc_dipsw_3, gpio_funct_gpio, gpio_data_dir_in, (gpio_pin_state_t)uc_dipsw_state_on);
    gpio_port_init(gpio_port_dd, (gpio_pin_t)uc_dipsw_4, gpio_funct_gpio, gpio_data_dir_in, (gpio_pin_state_t)uc_dipsw_state_on);
}