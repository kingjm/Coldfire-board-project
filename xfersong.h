//*******************************************************************************************************
// xfersong.h
//
// DESCRIPTION
//
// AUTHORS
// Jace Hensley (jehensle@asu.edu)
// Computer Systems Engineering
// Arizona State University
//********************************************************************************************************

#ifndef XFERSONG_H_
#define XFERSONG_H_
#include "uart.h"
#include "pit.h"
#include "uc_led.h"
#include "song.h"

typedef enum{
    xfer_start_state    = 0, //Reset counter and bytes in packet variables
    xfer_idle_state     = 1, //No char recieved
    xfer_begin_state    = 2, //First char received
    xfer_wait_state     = 3, //2nd & 3rd char recieved
    xfer_xfering_state  = 4, //transfer each song byte
    xfer_end_state      = 5,  //finished
    xfer_exit_state     = 6     // Exit tranfer_song function
}xfer_state_t;

typedef enum {
    led_off = 0,
    led_on = 1
} xfer_led_t;

static void pit0_xfer_callback();
song_t transfer_song();
void xfersong_callback();
static void xfersong_pb1_callback();
void xfersong_pb2_callback();

#endif

