//*******************************************************************************************************
// FILE NAME:	                uc_pushb.h
// PROJECT NUMBER:      Project #4
// NAME(S):                     James Pappas (ID# 1204791792) (jppappas)
//							            Jace Hensley (jehensle)
// EMAIL(S):                     James.Pappas@asu.edu
//								        jehensle@asu.edu
// COURSE:                      CSE325 Embedded Microprocessor Systems
// SEMESTER:                    Fall 2014
//**********************************************************************************************************************************
#include "global.h"

#ifndef UC_PUSHB_H_
#define UC_PUSHB_H_

#endif

typedef enum{
        uc_pushb_1 = 0,
        uc_pushb_2 = 1
}uc_pushb_t;

void uc_pushb_init();

void uc_pushb_debounce(uc_pushb_t const p_button);

__declspec(interrupt) void uc_pushb_1_isr();

__declspec(interrupt) void uc_pushb_2_isr();

void uc_pushb_set_callback();

void uc_pushb_debounce(uc_pushb_t const p_button);

