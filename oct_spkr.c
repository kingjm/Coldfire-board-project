//*******************************************************************************************************
// oct_spkr.c
//
// DESCRIPTION
//
// AUTHORS
// Jace Hensley (jehensle@asu.edu)
// Computer Systems Engineering
// Arizona State University
//********************************************************************************************************

#include "oct_spkr.h"
#include "pwm.h"


void speakerInit(){
    pwm_chan_init(channel_2, clk_SB, align_left, polarity_low);
}

void playNote(note_t note){
    switch(note.pitch){
    case pitch_b3:
        pwm_clk_config(clk_SB,  (uint8) 1, (uint8) 253);
        pwm_chan_start(channel_2, (uint8) 160, (uint8) 80);
        break;
    case pitch_c4:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 255);
        pwm_chan_start(channel_2, (uint8) 150, (uint8) 75);
        break;
    case pitch_c4_sharp:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 192);   
        pwm_chan_start(channel_2, (uint8) 188, (uint8) 94);
        break;
    case pitch_d4:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 198);
        pwm_chan_start(channel_2, (uint8) 172, (uint8) 86);
        break;
    case pitch_d4_sharp:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 171);
        pwm_chan_start(channel_2, (uint8) 188, (uint8) 94);
        break;
    case pitch_e4:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 158);   
        pwm_chan_start(channel_2, (uint8) 192, (uint8) 96);
        break;
    case pitch_f4:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 159);
        pwm_chan_start(channel_2, (uint8) 180, (uint8) 90);
        break;
    case pitch_f4_sharp:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 138);
        pwm_chan_start(channel_2, (uint8) 196, (uint8) 98);
        break;
    case pitch_g4:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 145);
        pwm_chan_start(channel_2, (uint8) 176, (uint8) 88);
        break;
    case pitch_g4_sharp:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 236); 
        pwm_chan_start(channel_2, (uint8) 102, (uint8) 51);
        break;
    case pitch_a4:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 247);
        pwm_chan_start(channel_2, (uint8) 92, (uint8) 46);
        break;
    case pitch_a4_sharp:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 165); 
        pwm_chan_start(channel_2, (uint8) 130, (uint8) 65);
        break;
    case pitch_b4:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 230); 
        pwm_chan_start(channel_2, (uint8) 88, (uint8) 44);
        break;
    case pitch_c5:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 147);
        pwm_chan_start(channel_2, (uint8) 130, (uint8) 65);
        break;
    case pitch_c5_sharp:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 110); 
        pwm_chan_start(channel_2, (uint8) 164, (uint8) 82);
        break;
    case pitch_d5:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 224);     
        pwm_chan_start(channel_2, (uint8) 76, (uint8) 38);
        break;
    case pitch_d5_sharp:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 103); 
        pwm_chan_start(channel_2, (uint8) 156, (uint8) 78);
        break;
    case pitch_e5:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 158);  
        pwm_chan_start(channel_2, (uint8) 96, (uint8) 48);
        break;
    case pitch_f5:
        pwm_clk_config(clk_SB, (uint8) 1, (uint8) 93);  
        pwm_chan_start(channel_2, (uint8) 154, (uint8) 77);
        break;  
    case pitch_mute:
        pwm_chan_stop(channel_2);
        break;
    }
}