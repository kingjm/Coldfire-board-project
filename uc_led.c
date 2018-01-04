//**************************************************************************************************************
// FILE NAME:               uc_led.c
// PROJECT NUMBER:   Project #1
// NAME:                      James Pappas
// EMAIL:                      James.Pappas@asu.edu
// COURSE:                   CSE325 Embedded Microprocessor Systems
// SEMESTER:                Fall 2014
//**************************************************************************************************************
#include "uc_led.h"
#include "gpio.h"

// Calls uc_led_off() four times to turn all LED's off.
void uc_led_all_off() {
    uc_led_off(uc_led_1);
    //uc_led_off(uc_led_2);
    uc_led_off(uc_led_3);
    uc_led_off(uc_led_4);
}

// Calls uc_led_on() four times to turn all LED's on.
void uc_led_all_on() {
    uc_led_on(uc_led_1);
    //uc_led_on(uc_led_2);
    uc_led_on(uc_led_3);
    uc_led_on(uc_led_4);
}

// Calls gpio_port_init() four times to initialize the pins of port TC that each LED is connected to.
void uc_led_init() {
    gpio_port_init(gpio_port_tc, (gpio_pin_t)(uc_led_1 - 1), gpio_funct_gpio, gpio_data_dir_out, (gpio_pin_state_t)gpio_pin_state_low);
   //gpio_port_init(gpio_port_tc, (gpio_pin_t)(uc_led_2 - 1), gpio_funct_gpio, gpio_data_dir_out, (gpio_pin_state_t)gpio_pin_state_low);
    gpio_port_init(gpio_port_tc, (gpio_pin_t)(uc_led_3 - 1), gpio_funct_gpio, gpio_data_dir_out, (gpio_pin_state_t)gpio_pin_state_low);
    gpio_port_init(gpio_port_tc, (gpio_pin_t)(uc_led_4 - 1), gpio_funct_gpio, gpio_data_dir_out, (gpio_pin_state_t)gpio_pin_state_low);
}

// Calls gpio_port_set_pin_state() to set the state of the pin in port TC for LED p_led to turn the LED off.
void uc_led_off(int p_led) {
    gpio_port_set_pin_state(gpio_port_tc, (gpio_pin_t)(p_led - 1), gpio_pin_state_low);
}

// Calls gpio_port_set_pin_state() to set the state of the pin in port TC for LED p_led to turn the LED on.
void uc_led_on(int p_led) {
    gpio_port_set_pin_state(gpio_port_tc, (gpio_pin_t)(p_led - 1), gpio_pin_state_high);
}

// Calls gpio_port_get_pin_state() to determine if LED p_led is on or off. It it is on, turn it off and if it is off, turn it on
void uc_led_toggle(int p_led) {
    if(gpio_port_get_pin_state(gpio_port_tc, (gpio_pin_t)(p_led - 1)) == gpio_pin_state_high) {
        uc_led_off(p_led - 1);
    }
    else
        uc_led_on(p_led - 1);
}
