//**************************************************************************************************************
// FILE NAME:               dtim.h
// PROJECT NUMBER:   Project #3
// NAME(S):                      James Pappas (ID# 1204791792) (jppappas)
//							  Jace Hensley (jehensle)
// EMAIL(S):                      James.Pappas@asu.edu
//								 jehensle@asu.edu
// COURSE:                   CSE325 Embedded Microprocessor Systems
// SEMESTER:                Fall 2014
//**********************************************************************************************************************************
#ifndef DTIM_H_
#define DTIM_H_

#include "support_common.h"
#include "int.h"

typedef enum { 
 dtim_0 = 0, // DMA timer 0
 dtim_1 = 1, // DMA timer 1
 dtim_2 = 2, // DMA timer 2
 dtim_3 = 3 // DMA timer 3
} dtim_t ;

void dtim_init_irq(dtim_t const p_timer, uint32 const p_usecs, int_isr_t const p_callback);

__declspec(interrupt) void dtim0_isr();
__declspec(interrupt) void dtim1_isr();
__declspec(interrupt) void dtim2_isr();
__declspec(interrupt) void dtim3_isr();
void dtim_busy_delay_ms(dtim_t const p_timer, int const p_msecs);

void dtim_busy_delay_us(dtim_t const p_timer, int const p_usecs);

void dtim_init(dtim_t const p_timer);

#endif