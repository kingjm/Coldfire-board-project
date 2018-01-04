//*****************************************************************************
// FILE NAME:                  main.c
// PROJECT NUMBER:      Project #4
// NAME(S):                     James Pappas (ID# 1204791792) (jppappas)
//                                      Jace Hensley (jehensle)
// EMAIL(S):                     James.Pappas@asu.edu
//                                      jehensle@asu.edu
// COURSE:                      CSE325 Embedded Microprocessor Systems
// SEMESTER:                    Fall 2014
//*****************************************************************************
#if (CONSOLE_IO_SUPPORT || ENABLE_UART_SUPPORT)
/* Standard IO is only possible if Console or UART support is enabled. */
#include <stdio.h>
#endif


#include "dtim.h"
#include "global.h"
#include "gpio.h"
#include "oct_rgb_led.h"
#include "pwm.h"
#include "pit.h"
#include "gpt.h"
#include "int.h"
#include "uc_led.h"
#include "uc_pushb.h"
#include "uc_dipsw.h"
#include "oct_spkr.h"
#include "song.h"
#include "note.h"
#include "xfersong.h"

typedef enum{
    idle = 0,
    play = 1,
    pause = 2,
    transfer = 3
}state_t;


void idle_mode();

volatile state_t state = idle;
volatile bool_t transfered = false;
volatile bool_t char_received = false;
bool_t pushb_2_pressed = false;
int duration;

song_t current_song; // Song to be played

static void pit0_callback(){
    uc_led_toggle(uc_led_1);
}


static void pit1_callback(){
    
}

static void uc_pushb2_callback(){
    if(state == play || state == pause){
        state = idle;
    }
    else if(state == idle){
        state = transfer;
    }
}

static void uc_pushb1_callback(){
    if(state == play){
        state = pause;
    }
    else if(state == pause){
        state = play;
    }
    else if(state == idle){
        state = play;
    }
    
}


static void hw_init(){
    int_inhibit_all();
    

    uc_pushb_init(uc_pushb_1, uc_pushb1_callback);
    uc_pushb_init(uc_pushb_2, uc_pushb2_callback);
    
    
    uart_init(1, 300, 8, 0, 8, 1, 2, 2);
    
    uc_led_init();
    
    dtim_init(dtim_0);
    
    speakerInit();
    
    int_uninhibit_all();
}

void transfer_mode(){
    
    current_song = transfer_song(); // Return the song_t object from transfer_mode and save it in current_song
    
    uc_pushb_set_callback(uc_pushb_2, uc_pushb2_callback); // Reconfigure the callback
    uc_pushb_set_callback(uc_pushb_1, uc_pushb1_callback);
    
    /*if(current_song != 0){
        transfered = true; // Set boolean to true
    }
    else if(current_song == 0){
        transfered = false; // Set boolean to false
    } */
    pit_disable(pit_timer_0);
    if(current_song.success){
        transfered = true;
    }
    else if(!current_song.success){
        transfered = false;
    }
    state = idle;
    idle_mode(); // Go back to idle mode after song transfer
}

int getDuration(int tempo, duration_t duration){
    switch(duration){
        case duration_32th:
            return tempo/8;
            break;
        case duration_32th_dot:
            return (tempo*3)/16;
            break;
        case duration_16th:
            return tempo/4;
            break;
        case duration_16th_dot:
            return (tempo*3)/8;
            break;
        case duration_8th:
            return tempo/2;
            break;
        case duration_8th_dot:
            return (tempo*3)/4;
            break;
        case duration_quarter:
            return tempo;
            break;
        case duration_quarter_dot:
            return (tempo*3);
            break;
        case duration_half:
            return tempo*2;
            break;
        case duration_half_dot:
            return tempo*3;
            break;
        case duration_whole:
            return tempo*4;
            break;
        case duration_double_whole:
            return (tempo*8);
            break;
    }
}

void play_mode(){
    if(transfered){
        
       //uc_led_toggle(uc_led_1);
        
        int currDuration;

        /*current_song.notes[0].duration = duration_16th;
        current_song.notes[0].pitch = pitch_c4;
            
        current_song.notes[1].duration = duration_double_whole;
        current_song.notes[1].pitch = pitch_e4;

        current_song.notes[2].duration = duration_quarter;
        current_song.notes[2].pitch = pitch_g4;

        current_song.notes[3].duration = duration_quarter;
        current_song.notes[3].pitch = pitch_e4;
           
        current_song.num_notes=4;
            
        current_song.tempo = 375; */
            
        while(1){
            int i;
            for(i = 0; i < current_song.num_notes; i++){
                uc_led_on(uc_led_1);
                playNote(current_song.notes[i]);
                currDuration = getDuration(current_song.tempo, current_song.notes[i].duration);
                dtim_busy_delay_ms(dtim_0, currDuration);
                                
                pwm_chan_stop(channel_2);
                uc_led_off(uc_led_1);
                dtim_busy_delay_ms(dtim_0, 25);
                
                while(state == pause){
                    
                }
                
                if(state == idle ||state == transfer){
                    uc_led_all_off();
                    state = idle;
                    idle_mode();
                } 
            }
            dtim_busy_delay_ms(dtim_0, 1000);
        }        
    }
   
    else{
        state = idle;
        idle_mode();
    }
}

void idle_mode(){
    uc_led_all_off(); // Turn all LED's off
    
    while(state==idle){ // While in idle, do nothing
        
    }
    
    if(state == play){ // If PB1 pressed, enter play mode
        play_mode();
    }
    else if(state == transfer){ // If PB2 pressed, enter tranfer mode
        transfer_mode(); // If PB2 pressed, etner transfer mode
    }
}


static void run(){
    idle_mode();
} // end run()

//Starts everything
 __declspec(noreturn) int main(){
    hw_init();
    run();
}
 
 

 
 