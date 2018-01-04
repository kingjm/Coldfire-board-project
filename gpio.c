//**************************************************************************************************************
// FILE NAME:               gpio.c
// PROJECT NUMBER:   Project #3
// NAME(S):                      James Pappas (ID# 1204791792) (jppappas)
//							  Jace Hensley (jehensle)
// EMAIL(S):                      James.Pappas@asu.edu
//								 jehensle@asu.edu
// COURSE:                   CSE325 Embedded Microprocessor Systems
// SEMESTER:                Fall 2014
//**********************************************************************************************************************************
#include "gpio.h"
#include "global.h"

static const uint32 GPIO_BASE = 0x40100000; // Base address of the GPIO module in the IPS
static const uint32 GPIO_DDR_BASE = GPIO_BASE + 0x18; // Base address of the DDR registers in the GPIO space
static const uint32 GPIO_SET_BASE = GPIO_BASE + 0x30; // Base address of the SET registers in the GPIO space
static const uint32 GPIO_CLR_BASE = GPIO_BASE + 0x48; // Base address of the CLR registers in the GPIO space
static const uint32 GPIO_PAR_BASE = GPIO_BASE + 0x60; // Base address of the PAR registers in the GPIO space
#define GPIO_SET(n) (*(vuint8 *)(GPIO_SET_BASE + (n))) // SET reg, n is GPIO_PORT_TC or GPIO_PORT_DD
#define GPIO_DDR(n) (*(vuint8 *)(GPIO_DDR_BASE + (n))) // DDR reg
#define GPIO_CLR(n) (*(vuint8 *)(GPIO_CLR_BASE + (n))) // CLR reg
#define GPIO_PAR(n) (*(vuint8 *)(GPIO_PAR_BASE + (n))) // PAR reg

/* --------------------------------------------------------------------------------------------------------------
-- gpio_port_init() : Called to initialize pin p_pin of GPIO port p_port for the function p_funct. If p_funct is
-- GPIO then configure the pin's data direction to be p_data_dir. If the pin is being configured as an output pin
-- set the state of the pin's output to p_state.
-- ------------------------------------------------------------------------------------------------------------*/
void gpio_port_init(gpio_port_t p_port, gpio_pin_t p_pin, gpio_funct_t p_funct,
gpio_data_dir_t p_data_dir, gpio_pin_state_t p_state) {
    switch (p_port) {
    case gpio_port_an:
    case gpio_port_dd:
        GPIO_CLR(p_port) &= ~(1 << p_pin); // Clears PAR
        GPIO_PAR(p_port)  &= ~(1 << p_pin); //Clear using GPIO_PAR(p_port);
        GPIO_PAR(p_port)  |= (p_funct << p_pin);
        break;
    case gpio_port_ta:
    case gpio_port_tc:
    case gpio_port_ub:
        GPIO_CLR(p_port) &= ~(0x1 << p_pin); // Clears PAR
        GPIO_PAR(p_port)  &= ~(0x3 << p_pin * 2); //Clear using GPIO_PAR(p_port);
        GPIO_PAR(p_port)  |= (p_funct << p_pin * 2);
        break;
    }
     
    // If set to GPIO
     if(p_funct == gpio_funct_gpio) {
         gpio_port_set_data_dir(p_port, p_pin, p_data_dir);
         
         // If set to output
         if(p_data_dir == gpio_data_dir_out) {
             gpio_port_set_pin_state(p_port, p_pin, p_state);
         }
     }
    
}

/* --------------------------------------------------------------------------------------------------------------
-- gpio_port_get_pin_state() : Returns the state of an input pin.
-- ------------------------------------------------------------------------------------------------------------*/
gpio_pin_state_t gpio_port_get_pin_state(gpio_port_t const p_port, gpio_pin_t const p_pin) {
    return (gpio_pin_state_t)((GPIO_SET(p_port) & (1 << p_pin)) >> p_pin);
}

/* --------------------------------------------------------------------------------------------------------------
-- gpio_port_set_data_dir() : Sets the data direction of p_pin to Output (p_data_dir = gpio_pin_data_dir_out) or
-- Input (p_data_dir = gpio_pin_data_dir_in).
-- ------------------------------------------------------------------------------------------------------------*/
static void gpio_port_set_data_dir(gpio_port_t p_port, gpio_pin_t p_pin, gpio_data_dir_t p_data_dir) {
    if(p_data_dir == gpio_data_dir_in)
        GPIO_DDR(p_port) &= ~(1 << p_pin);
    else if(p_data_dir == gpio_data_dir_out)
        GPIO_DDR(p_port) |= (1 << p_pin);
}

/* --------------------------------------------------------------------------------------------------------------
-- gpio_port_set_pin_state() : Sets the state of output pin p_pin to be either high (p_state =
-- gpio_pin_state_high) or low (p_state = gpio_pin_state_low).
-- ------------------------------------------------------------------------------------------------------------*/
void gpio_port_set_pin_state(gpio_port_t const p_port, gpio_pin_t const p_pin, gpio_pin_state_t const p_state) {
    if(p_state == gpio_pin_state_high)
        GPIO_SET(p_port) |= (1 << p_pin);
    else
        GPIO_CLR(p_port) &= ~(1 << p_pin);
}