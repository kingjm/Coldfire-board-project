//*****************************************************************************
// FILE NAME:					pit.h
// PROJECT:						Project04
// NAME(S):						James Pappas (jppappas)
//										Jace Hensley (jehensle)
// EMAIL(S):						James Pappas (James.Pappas@asu.edu)
//										jehensle@asu.edu
// COURSE:						CSE 325 - Embedded Microprocessor Systems
// SEMESTER:					Fall 2014
//*****************************************************************************
#include "global.h"
#include "int.h"

#ifndef PIT_H_
#define PIT_H_

typedef enum{
    pit_timer_0 = 0,
    pit_timer_1 = 1
}pit_timer_t;


void pit_disable(pit_timer_t const);
void pit_init(pit_timer_t, uint8, uint16, int_isr_t const);
void pit_enable(pit_timer_t const);
__declspec(interrupt) void pit0_isr();
__declspec(interrupt) void pit1_isr();


#endif /* PIT_H_ */
