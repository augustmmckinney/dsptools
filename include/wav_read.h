#ifndef WAV_READ_H
#define WAV_READ_H

#include "wav_data.h"

/*	wave_read() accepts a .wav file, and returns a wav_data
 *  struct containing info about the structure of the
 *	file and a pointer to the audio samples stored in memory
 */

struct wav_data wav_read(char* filepath);

#endif
