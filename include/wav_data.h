#ifndef WAV_DATA_H
#define WAV_DATA_H

//	wav_data is a struct used by the wav_read() and wav_write() functions	

struct wav_data {
	int error;
  int16_t audio_format, channels, block_align, bit_depth;
	int32_t chunk_size, fmt_subchunk_size, data_subchunk_size, sample_rate, byte_rate, samples;
	int8_t* data;
};

#endif
