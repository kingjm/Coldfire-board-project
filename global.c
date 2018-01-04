//*********************************************************************************************************************************
// FILE NAME:               global.c
// PROJECT NUMBER:   Project #3
// NAME(S):                      James Pappas (ID# 1204791792) (jppappas)
//							  Jace Hensley (jehensle)
// EMAIL(S):                      James.Pappas@asu.edu
//								 jehensle@asu.edu
// COURSE:                   CSE325 Embedded Microprocessor Systems
// SEMESTER:                Fall 2014
//**********************************************************************************************************************************
// FILE: global.c
//
// DESCRIPTION
// See comments in global.h.
//
// AUTHORS
// Kevin R. Burger (burgerk@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe, AZ 85287-8809
// http://www.devlang.com
//**********************************************************************************************************************************
#include "global.h"

//==================================================================================================================================
// Public Global Constant Definitions
//==================================================================================================================================

int const SYS_CLOCK_FREQ_HZ  = 80000000;
int const SYS_CLOCK_FREQ_KHZ = SYS_CLOCK_FREQ_HZ / 1000;
int const SYS_CLOCK_FREQ_MHZ = SYS_CLOCK_FREQ_KHZ / 1000;

