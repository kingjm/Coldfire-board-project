//*********************************************************************************************************************************
// FILE NAME:               dtim.c
// PROJECT NUMBER:   Project #3
// NAME(S):                      James Pappas (ID# 1204791792) (jppappas)
//							  Jace Hensley (jehensle)
// EMAIL(S):                      James.Pappas@asu.edu
//								 jehensle@asu.edu
// COURSE:                   CSE325 Embedded Microprocessor Systems
// SEMESTER:                Fall 2014
//**********************************************************************************************************************************
#include "dtim.h"
#include "global.h"
#include "int.h"

// The base address in the peripheral register range of the DTIM module registers.
static uint32 const DTIM_BASE = 0x40000400;

// The addresses of the DTIM registers for timers n = 0, 1, 2, and 3.
#define DTIM_DTCN(timer) *(volatile uint32 *) (DTIM_BASE + 0x0C + ((timer) << 6))
#define DTIM_DTCR(timer) *(volatile uint32 *) (DTIM_BASE + 0x08 + ((timer) << 6))
#define DTIM_DTER(timer) *(volatile uint8 *) (DTIM_BASE + 0x03 + ((timer) << 6))
#define DTIM_DTMR(timer) *(volatile uint16 *) (DTIM_BASE + 0x00 + ((timer) << 6))
#define DTIM_DTRR(timer) *(volatile uint32 *) (DTIM_BASE + 0x04 + ((timer) << 6))
#define DTIM_DTXMR(timer) *(volatile uint8 *) (DTIM_BASE + 0x02 + ((timer) << 6))

static int_isr_t g_dtim_callbacks[4] = {0, 0, 0, 0};
static int_isr_t g_dtim_isrs[4] = {&dtim0_isr, &dtim1_isr, &dtim2_isr, &dtim3_isr};

/*-----------------------------------------------------------------------------------------------------------------------
-- dtim_init_irq:  Initializes DMA timer p_timer to generate interrupt requests every p_usecs microseconds. p_callback
-- is a function pointer to the user's callback function.
-----------------------------------------------------------------------------------------------------------------------*/
void dtim_init_irq(dtim_t const p_timer, uint32 const p_usecs, int_isr_t const p_callback) {
    // Reset the timer
    DTIM_DTMR(p_timer) |= 0x0001; // 0000 0000 0000 0001
    DTIM_DTMR(p_timer) &= ~0x0001; // 1111 1111 1111 1110
    
    // Initialize DTMR (DMA Timer Mode Register)
    DTIM_DTMR(p_timer) = 0x4F1A; //  01001111 00 0 1 1 01 0 = 0100 1111 0001 1010 = 0x4F1A
    
    // Initialize DTXMR (DMA Timer Extended Mode Register)
    DTIM_DTXMR(p_timer) = 0x40; // 0 1 00000 0 = 0100 0000 = 0x40
    
   // Initialize DTCN (DMA Timer Counter Register)
    DTIM_DTCN(p_timer) = 0;
    
    // Initialize DTRR (DMA Timer Reference Register
    DTIM_DTRR(p_timer) = p_usecs - 1;
    
    // Initialize DTER (DMA Timer Event Register)
    DTIM_DTER(p_timer) |= 0x02; // 000000 1 0 = 0000 0010 = 0x02
    
    //Configure interrupt handling for the DMA timer
    g_dtim_callbacks[p_timer] = p_callback;
    int_config(DTIM_INT_SRC(p_timer), DTIM_INT_LVL(p_timer), DTIM_INT_PRI(p_timer), g_dtim_isrs[p_timer]);
    
    // Enable timer
    DTIM_DTMR(p_timer) |= 0x0001; 
}

/*-----------------------------------------------------------------------------------------------------------------------
-- dtim0_isr: ISR for DMA timer 0.
-----------------------------------------------------------------------------------------------------------------------*/
__declspec(interrupt) void dtim0_isr() {
    DTIM_DTER(0) |= 0x0002; 
    if(g_dtim_callbacks[0] != 0)
        g_dtim_callbacks[0]();
}

/*-----------------------------------------------------------------------------------------------------------------------
-- dtim1_isr: ISR for DMA timer 1.
-----------------------------------------------------------------------------------------------------------------------*/
__declspec(interrupt) void dtim1_isr() {
    DTIM_DTER(1) |= 0x0002; 
    if(g_dtim_callbacks[1] != 0)
        g_dtim_callbacks[1]();
}

/*-----------------------------------------------------------------------------------------------------------------------
-- dtim2_isr: ISR for DMA timer 2.
-----------------------------------------------------------------------------------------------------------------------*/
__declspec(interrupt) void dtim2_isr() {
    DTIM_DTER(2) |= 0x0002; 
    if(g_dtim_callbacks[2] != 0)
        g_dtim_callbacks[2]();
}

/*-----------------------------------------------------------------------------------------------------------------------
-- dtim3_isr: ISR for DMA timer 3.
-----------------------------------------------------------------------------------------------------------------------*/
__declspec(interrupt) void dtim3_isr() {
    DTIM_DTER(3) |= 0x0002; 
    if(g_dtim_callbacks[3] != 0)
        g_dtim_callbacks[3]();
}

/*-----------------------------------------------------------------------------------------------------------------------
-- dtim_busy_delay_ms: Delay the mc for p_msecs. Calls dtim_busy_delay_us and converts ms to us (1000 * p_msecs)
-----------------------------------------------------------------------------------------------------------------------*/
void dtim_busy_delay_ms(dtim_t const p_timer, int const p_msecs) {
    if(p_msecs <= 4294967 )
        dtim_busy_delay_us(p_timer, 1000 * p_msecs);
}

/*-----------------------------------------------------------------------------------------------------------------------
-- dtim_busy_delay_us: Set fields ER, CN, RR, MR in the data timer field for delay function. Delays for p_usecs by putting
-- processor in infinite while loop until bit 0 of ER field is 1.
-----------------------------------------------------------------------------------------------------------------------*/
void dtim_busy_delay_us(dtim_t const p_timer, int const p_usecs) {
    DTIM_DTER(p_timer) = 0x03; // 000000 1 1 = 0000 0011 = 0x03
    DTIM_DTCN(p_timer) = 0x00000000; // Any value would suffice
    DTIM_DTRR(p_timer) = (uint32)(p_usecs - 1);
    DTIM_DTMR(p_timer) |= 0x0001; // Start counting
    while (~DTIM_DTER(p_timer) & 0x02) {}
}

/*-----------------------------------------------------------------------------------------------------------------------
-- dtim_init: [from project2] Initialize the timer.
-----------------------------------------------------------------------------------------------------------------------*/
void dtim_init(dtim_t const p_timer) {
    DTIM_DTMR(p_timer) |= 0x0001; // 0000 0000 0000 0001
    DTIM_DTMR(p_timer) &= ~0x0001; // 1111 1111 1111 1110
    DTIM_DTMR(p_timer) = 0x4F02; // 01001111 00 0 0 0 01 0 = 0100 1111 0000 0010 = 0x4F02
    DTIM_DTXMR(p_timer) = 0x40; //// 0 1 00000 0 = 0100 0000 = 0x40
}


