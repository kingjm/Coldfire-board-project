//*********************************************************************************************************************************
// FILE NAME:                   global.h
// PROJECT NUMBER:      Project #4
// NAME(S):                     James Pappas (ID# 1204791792) (jppappas)
//                                      Jace Hensley (jehensle)
// EMAIL(S):                     James.Pappas@asu.edu
//                                      jehensle@asu.edu
// COURSE:                      CSE325 Embedded Microprocessor Systems
// SEMESTER:                    Fall 2014
//**********************************************************************************************************************************
//**********************************************************************************************************************************
// FILE: global.h
//
// DECRIPTION
// Global declarations.
//
// AUTHORS
// Kevin R. Burger (burgerk@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe, AZ 85287-8809
// http://www.devlang.com
//**********************************************************************************************************************************
#ifndef GLOBAL_H
#define GLOBAL_H

#include "support_common.h"

//==================================================================================================================================
// Public Type Definitions
//==================================================================================================================================

typedef enum {
    false = 0,
    true  = 1
} bool_t;

//==================================================================================================================================
// Public Preprocessor Macros
//==================================================================================================================================

//==================================================================================================================================
// Public Global Constant Declarations
//==================================================================================================================================

extern int const SYS_CLOCK_FREQ_HZ;
extern int const SYS_CLOCK_FREQ_KHZ;
extern int const SYS_CLOCK_FREQ_MHZ;

//==================================================================================================================================
// Public Function Declarations
//==================================================================================================================================

#endif
