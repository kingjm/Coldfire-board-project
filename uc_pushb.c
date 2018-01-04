//*******************************************************************************************************
// FILE NAME:	                uc_pushb.c
// PROJECT NUMBER:      Project #4
// NAME(S):                     James Pappas (ID# 1204791792) (jppappas)
//							            Jace Hensley (jehensle)
// EMAIL(S):                     James.Pappas@asu.edu
//								        jehensle@asu.edu
// COURSE:                      CSE325 Embedded Microprocessor Systems
// SEMESTER:                    Fall 2014
//**********************************************************************************************************************************

#include "global.h"
#include "uc_pushb.h"
#include "gpio.h"
#include "gpt.h"
#include "int.h"

static int_isr_t g_callbacks[]={0,0};

void uc_pushb_init(uc_pushb_t const p_button, int_isr_t const p_callback){
    g_callbacks[(int)p_button] = p_callback;
    
    gpio_port_init(gpio_port_ta, (gpio_pin_t)p_button, gpio_funct_primary, gpio_data_dir_in, gpio_pin_state_x);
    
    gpt_disable();
    gpt_incap_config((gpt_pin_t)p_button, gpt_incap_edge_falling);
    
    if(p_button == uc_pushb_1){
        int_config(GPT_INT_SRC(uc_pushb_1), 4, GPT_INT_PRI(uc_pushb_1), uc_pushb_1_isr);
    }
    else{
        int_config(GPT_INT_SRC(uc_pushb_2), 4, GPT_INT_PRI(uc_pushb_2), uc_pushb_2_isr);
    }
    gpt_enable();
}


__declspec(interrupt) void uc_pushb_1_isr(){
   uc_pushb_debounce(uc_pushb_1);
    gpt_clr_flag(gpt_pin_0);
    if(g_callbacks[0]!= 0){
        (*(g_callbacks[0]))();
    }
}

__declspec(interrupt) void uc_pushb_2_isr(){
    uc_pushb_debounce(uc_pushb_2);
    gpt_clr_flag(gpt_pin_1);
    if(g_callbacks[1] != 0){
        (*(g_callbacks[1]))();
    }
}

void uc_pushb_set_callback(uc_pushb_t const p_button, int_isr_t const p_callback) {
    g_callbacks[(int)p_button] = p_callback;
}

void uc_pushb_debounce(uc_pushb_t const p_button) {
    uint8 signal = 0x01;
    uint16 state = 0x0000;
    do {
        state = (state << 1) | (uint16)signal | 0xE000;
        signal = (uint8)(~(int)MCF_GPT_GPTPORT >> p_button) & 0x01;
    } while (state != 0xF000);
}
