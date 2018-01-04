//*******************************************************************************************************
// song.c
//
// DESCRIPTION
//
// AUTHORS
// Jace Hensley (jehensle@asu.edu)
// Computer Systems Engineering
// Arizona State University
//********************************************************************************************************

#include "song.h"

song_t createSong(int tempo, int num_notes, note_t notes[256]){
    song_t newSong;
    int i;
    for(i=0; i<256; i++){
        newSong.notes[i] = notes[i];
    }
    newSong.num_notes = num_notes;
    newSong.tempo = tempo;
}


int getTempo(song_t song){
    return song.tempo;
}

int getNumNotes(song_t song){
    return song.num_notes;
}

void setTempo(song_t song, int tempo){
    song.tempo = tempo;
}

void setNumNotes(song_t song, int num_notes){
    song.num_notes = num_notes;
}

void setNotes(song_t song, note_t notes[256]){
    int i;
    for(i=0; i<256; i++){
        song.notes[i] = notes[i];
    }
    
}
