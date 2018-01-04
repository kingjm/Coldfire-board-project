//*****************************************************************************
// FILE NAME:					pit.c
// PROJECT:						Project04
// NAME(S):						James Pappas (jppappas)
//										Jace Hensley (jehensle)
// EMAIL(S):						James Pappas (James.Pappas@asu.edu)
//										jehensle@asu.edu
// COURSE:						CSE 325 - Embedded Microprocessor Systems
// SEMESTER:					Fall 2014
//*****************************************************************************
#include "pit.h"
#include "int.h"
#include "global.h"

static int_isr_t g_pit_callbacks[2] = {0,0};
static int_isr_t g_pit_isrs[2] = {pit0_isr, pit1_isr};

void pit_init(pit_timer_t n, uint8 p_prescaler, uint16 p_pmr, int_isr_t const p_callback){

    MCF_PIT_PCSR(n) = 0; // Clear the whole register
    MCF_PIT_PCSR(n) |= MCF_PIT_PCSR_PRE(p_prescaler);
    MCF_PIT_PCSR(n) &= ~MCF_PIT_PCSR_DOZE; // 0b01000000
    MCF_PIT_PCSR(n) |= MCF_PIT_PCSR_DBG;
    MCF_PIT_PCSR(n) |= MCF_PIT_PCSR_OVW;
    MCF_PIT_PCSR(n) |= MCF_PIT_PCSR_PIE;
    MCF_PIT_PCSR(n) |= MCF_PIT_PCSR_PIF;
    MCF_PIT_PCSR(n) |= MCF_PIT_PCSR_RLD;
    MCF_PIT_PMR(n) = MCF_PIT_PMR_PM(p_pmr);
    int_config(PIT_INT_SRC(n), PIT_INT_LVL(n), PIT_INT_PRI(n), g_pit_isrs[n]);
    g_pit_callbacks[n] = p_callback;
}

void pit_disable(pit_timer_t const n){
    switch(n){
        case pit_timer_0:
            MCF_PIT0_PCSR &= ~(MCF_PIT_PCSR_EN);
            break;
        case pit_timer_1:
            MCF_PIT1_PCSR &= ~(MCF_PIT_PCSR_EN);
            break;
    }
}

void pit_enable(pit_timer_t const n){
    switch(n){
        case pit_timer_0:
            MCF_PIT0_PCSR |= (MCF_PIT_PCSR_EN);
            break;
        case pit_timer_1:
            MCF_PIT1_PCSR |= (MCF_PIT_PCSR_EN);
            break;
    }
}

__declspec(interrupt) void pit0_isr(){
    MCF_PIT0_PCSR |= MCF_PIT_PCSR_PIF;
    if(g_pit_callbacks[0]){
        g_pit_callbacks[0]();
    }
}

__declspec(interrupt) void pit1_isr(){
    MCF_PIT1_PCSR |= MCF_PIT_PCSR_PIF;
    if(g_pit_callbacks[1]){
        g_pit_callbacks[1]();
    }
}

