#ifndef WAVIN_H
#define WAVIN_H

/*	wavein accepts a .wav file, and returns a wav_data
 *  struct containing info about the structure of the
 *	file and an array containing the audio samples
 */

struct wav_data {
	int error;
  int16_t audio_format, channels, block_align, bit_depth;
	int32_t chunk_size, subchunk_size, sample_rate, byte_rate, samples;
};

struct wav_data wavin(char* filepath);

#endif
