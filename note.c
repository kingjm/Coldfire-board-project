//*******************************************************************************************************
// note.c
//
// DESCRIPTION
//
// AUTHORS
// Jace Hensley (jehensle@asu.edu)
// Computer Systems Engineering
// Arizona State University
//********************************************************************************************************

#include "note.h"

note_t createNote(pitch_t pitch, duration_t duration){
    note_t newNote;
    newNote.duration = duration;
    newNote.pitch = pitch;
    return newNote;
}