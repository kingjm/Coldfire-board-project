//*******************************************************************************************************
// song.h
//
// DESCRIPTION
//
// AUTHORS
// Jace Hensley (jehensle@asu.edu)
// Computer Systems Engineering
// Arizona State University
//********************************************************************************************************
#ifndef SONG_H_
#define SONG_H_

#include "note.h"
#include "global.h"



typedef struct{
    note_t notes[256];
    int num_notes;
    int tempo;
    bool_t success;
}song_t;

song_t createSong(int tempo, int num_notes, note_t notes[]);
int getTempo(song_t song);
int getNumNotes(song_t song);
void setTempo(song_t song, int tempo);
void setNumNotes(song_t song, int num_notes);
void setNotes(song_t song, note_t notes[]);
song_t emptySong();

#endif

