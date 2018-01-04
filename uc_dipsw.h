//**************************************************************************************************************
// FILE NAME:                      uc_dipsw.h
// PROJECT NUMBER:          Project #4
// NAME(S):                         James Pappas (ID# 1204791792) (jppappas)
//                                         Jace Hensley (jehensle)
// EMAIL(S):                         James.Pappas@asu.edu
//                                         jehensle@asu.edu
// COURSE:                         CSE325 Embedded Microprocessor Systems
// SEMESTER:                       Fall 2014
//**************************************************************************************************************
#include "global.h"

#ifndef UC_DIPSW_H_
#define UC_DIPSW_H_

typedef enum { 
 uc_dipsw_1 = 4, // Represents subswitch 1
 uc_dipsw_2 = 5, // Represents subswitch 2
 uc_dipsw_3 = 6, // Represents subswitch 3
 uc_dipsw_4 = 7 // Represents subswitch 4
} uc_dipsw_t; 

typedef enum { 
 uc_dipsw_state_off = 1, // Represents the Off state
 uc_dipsw_state_on = 0 // Represents the On state
} uc_dipsw_state_t; 


uc_dipsw_state_t uc_dipsw_get_state(uc_dipsw_t p_switch);

void uc_dipsw_init();


#endif /* UC_DIPSW_H_ */
