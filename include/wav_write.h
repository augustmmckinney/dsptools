#ifndef WAV_WRITE_H
#define WAV_WRITE_H

#include "wav_data.h"

/*	wav_write() accepts a filepath and a wav_data struct, and writes
 *  a .wav file at the designated filepath
 */

int wav_write(char* filepath, struct wav_data data);

#endif
