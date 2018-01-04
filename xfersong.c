//*******************************************************************************************************
// xfersong.c
//
// DESCRIPTION
//
// AUTHORS
// Jace Hensley (jehensle@asu.edu)
// Computer Systems Engineering
// Arizona State University
//********************************************************************************************************

#include "xfersong.h"
#include "uc_pushb.h"

uint8 g_rx_buf[531];
int g_bytes_in_packet;
int g_rx_cnt;
xfer_state_t xfer_state;
static song_t l_song; // Create local song variable to fill and return
xfer_led_t led1 = led_off;

// When UART receives a byte
void xfersong_callback(){
    g_rx_buf[g_rx_cnt] = get_char();    // Store the byte in the buffer
    if(led1 == led_off) {
        uc_led_on(uc_led_1);
        led1 = led_on;
    }
    else {
        uc_led_off(uc_led_1);
        led1 = led_off;
    }
    //uc_led_toggle(uc_led_1);            // Toggle the LED
    g_rx_cnt++;                         // Increment the counter
}

static void pit0_xfer_callback(){
    if(led1 == led_off) {
        uc_led_on(uc_led_1);
        led1 = led_on;
    }
    else {
        uc_led_off(uc_led_1);
        led1 = led_off;
    }
    // uc_led_toggle(uc_led_1);
}

static void xfersong_pb2_callback() {
    if (xfer_state == xfer_idle_state) {
        xfer_state = xfer_exit_state;  
    }

}

static void xfersong_pb1_callback() {
    //nothing

}



// Will return a song_t object to main.c
song_t transfer_song(){
    int secondByte; // Second byte holds the most significant 8 bits of total number of bytes
    int thirdByte;  // Third byte holds the least significant 8 bits of total number of bytes
    int ninthByte;  // Ninth byte holds the most significant 8 bits of the tempo
    int tenthByte;  // Tenth byte holds the least signifcant 8 bits of the tempo
    int eleventhByte;  // 11th byte holds the most significant 8 bits of the tempo
    int twelthByte;  // 12th byte holds the least signifcant 8 bits of the tempo
    
    int i; // Counter
    int noteCount; 
    
    uc_pushb_set_callback(uc_pushb_2, xfersong_pb2_callback); // Configure push button 2 for different functionality
    uc_pushb_set_callback(uc_pushb_1, xfersong_pb1_callback);
    xfer_state = xfer_start_state; // Start state
    //uart_channel_enable(1, xfersong_callback); // Turn on UART
    pit_init(pit_timer_0, (uint8) 0x7, (uint16) 78124,  pit0_xfer_callback);
    pit_enable(pit_timer_0); // Enable the PIT to toggle LED at 2Hz

    while(xfer_state != xfer_exit_state){
        switch(xfer_state){
            case xfer_start_state:
                g_rx_cnt = 0;                   // Initialize the counter to 0
                g_bytes_in_packet = 0;          // Reset number of bytes to 0
                xfer_state = xfer_idle_state;   // Go to next state
                break;
            case xfer_idle_state:
                uart_channel_enable(1, xfersong_callback);  // Enable the UART module to start receiving bytes at 300baud
                while(g_rx_cnt == 0){                       // Wait in an infinite while loop until the first byte is received
                    if(xfer_state == xfer_exit_state){     // While waiting, check to see if PB2 is pressed. If pressed,
                                     // break out of switch and transfer_song function
                        return l_song;
                    }
                                               
                                                  
                }
                xfer_state = xfer_begin_state;              // After first character received, go to the next state
                break;
            case xfer_begin_state:
                pit_disable(pit_timer_0);       // Disable PIT0 to stop toggling LED1
                uc_led_on(uc_led_1);            // Turn LED1 on
                xfer_state = xfer_wait_state;   // Go to next state
                break;
            case xfer_wait_state:

                while(g_rx_cnt <= 3) {
                    if(g_rx_cnt == 2)
                        secondByte = 256 * (int)g_rx_buf[1]; // Retrieve the most significant 8 bits and turn into int
                    else if(g_rx_cnt == 3)
                        thirdByte = (int)g_rx_buf[2];        // Retrieve the least significant 8 bits and turn into int
                }
                
                g_bytes_in_packet = secondByte + thirdByte; // Add the least and most significant bytes together to get total bytes as integer
                xfer_state = xfer_xfering_state;            // Go to next state
                break;
            case xfer_xfering_state:
                while (g_rx_cnt < g_bytes_in_packet) {      // Retrieve all the bytes in the packet
                    
                }
                xfer_state = xfer_end_state;               // Go to next state
                break;
            case xfer_end_state:
                uc_led_on(uc_led_1);                        // Turn LED1 on
                pit_enable(pit_timer_0);                    // Enable Pit0 again to flash LED1 at 2Hz (toggle every .25s)
                
                // Extract info from buffer and store into a song_t
                
                ninthByte = 256 * (int)g_rx_buf[8]; // Retrieve the most significant 8 bits and turn into int
                tenthByte = (int)g_rx_buf[9];        // Retrieve the least significant 8 bits and turn into int
                
                l_song.tempo = ninthByte + tenthByte;  // Get the tempo from the sum of the ninth and tenth byte
                
                                
                eleventhByte = 256 * (int)g_rx_buf[10]; // Retrieve the most significant 8 bits and turn into int
                twelthByte = (int)g_rx_buf[11];        // Retrieve the least significant 8 bits and turn into int
                                
                l_song.num_notes = eleventhByte + twelthByte + 1;  // Get the number of notes from the sum of the 11th and 12th byte
                
                // Parse each note into a song_t structure
                noteCount = 0;

                
                for(i = 19; i < g_bytes_in_packet; i++) {
                    if((i % 2) == 1)
                        l_song.notes[(i-19-noteCount)].pitch = (pitch_t)g_rx_buf[i];
                    else {
                        l_song.notes[(i-20-noteCount)].duration = (duration_t)g_rx_buf[i];
                        noteCount++;
                    }
                }
                
                xfer_state = xfer_start_state; // Go back to start state
                l_song.success = true;
                break;
        }
    }
    
    uart_channel_disable(1); // Turn off UART
    uc_led_off(uc_led_1); // Turn off LED1
    uc_led_off(uc_led_3); // Turn off LED3
    uc_led_off(uc_led_4); // Turn off LED4

    return l_song;
}






