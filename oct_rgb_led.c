//*****************************************************************************
// FILE NAME:					oct_rgb_led.c
// PROJECT:						Project04
// NAME(S):						James Pappas (jppappas)
//										Jace Hensley (jehensle)
// EMAIL(S):						James Pappas (James.Pappas@asu.edu)
//										jehensle@asu.edu
// COURSE:						CSE 325 - Embedded Microprocessor Systems
// SEMESTER:					Fall 2014
//*****************************************************************************
#include "oct_rgb_led.h"
#include "gpio.h"
#include "pwm.h"
#include "pit.h"

typedef struct {
   int ledColor[3];
   oct_rgb_led_state_t ledState;
}oct_rgb_led;

oct_rgb_led ledArray[3];
int currentLed; // 1-3 depeding on which LED


void oct_rgb_led_all_off(){
    int i;
    for (i = 0; i < 3; i++) {
        oct_rgb_led_off(i);
    }
}

void oct_rgb_led_all_on(){
    int i;
    for (i =0; i < 3; i++) {
          oct_rgb_led_on(i);
      }
}

void oct_rgb_led_init(){
    gpio_port_init(gpio_port_an, (gpio_pin_t)oct_rgb_led_1, gpio_funct_gpio, gpio_data_dir_out, gpio_pin_state_low);
    gpio_port_init(gpio_port_an, (gpio_pin_t)oct_rgb_led_2, gpio_funct_gpio, gpio_data_dir_out, gpio_pin_state_low);
    gpio_port_init(gpio_port_an, (gpio_pin_t)oct_rgb_led_3, gpio_funct_gpio, gpio_data_dir_out, gpio_pin_state_low);
    
    pwm_clk_config(clk_SA, (uint8)0, (uint8)0x64); // Set SA to 200 kHz
    pwm_clk_config(clk_SB, (uint8)0, (uint8)0x64); // Set SB to 200 kHz
    
    pwm_chan_init(channel_4, clk_SA, align_left, polarity_low);
    pwm_chan_init(channel_5, clk_SB, align_left, polarity_low);
    pwm_chan_init(channel_6, clk_SA, align_left, polarity_low);
    
    oct_rgb_led_all_off();
    
    currentLed = 0;
    
    pit_init(pit_timer_0, (uint8)0x2, (uint16)49999, oct_rgb_led_callback);
    
    pit_enable(pit_timer_0);
}

void oct_rgb_led_off(int p_led){
    ledArray[p_led].ledState = oct_rgb_led_state_off;
}

void oct_rgb_led_on(int p_led){
    ledArray[p_led].ledState = oct_rgb_led_state_on;
}

void oct_rgb_led_set_color(int p_led, oct_rgb_led_color_t p_color){

    switch(p_color){
        case oct_rgb_led_color_red:
            ledArray[p_led].ledColor[0] = 22;
            ledArray[p_led].ledColor[1] = 0;
            ledArray[p_led].ledColor[2] = 0;
            break;
        case oct_rgb_led_color_orange:
            ledArray[p_led].ledColor[0] = 22;
            ledArray[p_led].ledColor[1] = 12;
            ledArray[p_led].ledColor[2] = 0;
            break;
        case oct_rgb_led_color_yellow:
            ledArray[p_led].ledColor[0] = 22;
            ledArray[p_led].ledColor[1] = 62;
            ledArray[p_led].ledColor[2] = 0;
            break;
        case oct_rgb_led_color_green:
            ledArray[p_led].ledColor[0] = 0;
            ledArray[p_led].ledColor[1] = 62;
            ledArray[p_led].ledColor[2] = 0;
            break;
        case oct_rgb_led_color_indigo:
            ledArray[p_led].ledColor[0] = 6;
            ledArray[p_led].ledColor[1] = 0;
            ledArray[p_led].ledColor[2] = 22;
            break;
        case oct_rgb_led_color_blue:
            ledArray[p_led].ledColor[0] = 0;
            ledArray[p_led].ledColor[1] = 0;
            ledArray[p_led].ledColor[2] = 42;
            break;
        case oct_rgb_led_color_violet:
            ledArray[p_led].ledColor[0] = 72;
            ledArray[p_led].ledColor[1] = 0;
            ledArray[p_led].ledColor[2] = 42;
            break;
        case oct_rgb_led_color_white:
            ledArray[p_led].ledColor[0] = 56;
            ledArray[p_led].ledColor[1] = 126;
            ledArray[p_led].ledColor[2] = 82;
            break;
        }
    

}

void oct_rgb_led_toggle(int p_led){
    if(ledArray[p_led].ledState == oct_rgb_led_state_off)
        ledArray[p_led].ledState = oct_rgb_led_state_on;
    else
        ledArray[p_led].ledState = oct_rgb_led_state_off;
}

static void oct_rgb_led_callback(){
    
    int l_pin;
    
    if(currentLed == 0)
        l_pin = 4;
    else if(currentLed == 1)
        l_pin = 6;
    else
        l_pin = 7;
    
    gpio_port_set_pin_state(gpio_port_an, (gpio_pin_t)l_pin, gpio_pin_state_low);
    if(ledArray[currentLed].ledState == oct_rgb_led_state_on) {
        pwm_chan_start(channel_4, (uint8)200, (uint8)(ledArray[currentLed].ledColor[0]));
        pwm_chan_start(channel_5, (uint8)200, (uint8)(ledArray[currentLed].ledColor[1]));
        pwm_chan_start(channel_6, (uint8)200, (uint8)(ledArray[currentLed].ledColor[2]));
        gpio_port_set_pin_state(gpio_port_an, (gpio_pin_t)l_pin, gpio_pin_state_high);
    }
    
    currentLed = ((currentLed + 1) % 3);
}
