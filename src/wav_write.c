#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../include/wav_data.h"

int wav_write(char* filepath, struct wav_data data) {

	// instantiate variables
	FILE* fptr;

	// open filepath for binary write
	fptr = fopen(filepath, "wb");
	if(fptr == NULL) {
		perror("error");
		return 1;
	}

	// write RIFF header
	fwrite("RIFF", sizeof(char), 4, fptr);

	// write file size - 8
	fwrite(&data.chunk_size, sizeof(int32_t), 1, fptr);

	// write WAVE format
	fwrite("WAVE", sizeof(char), 4, fptr);
	
	// write "fmt " chunk ID
	fwrite("fmt ", sizeof(char), 4, fptr);

	// write length of format data
	fwrite(&data.fmt_subchunk_size, sizeof(int32_t), 1, fptr);

	// write type of format
	fwrite(&data.audio_format, sizeof(int16_t), 1, fptr);
	
	// write # of channels
	fwrite(&data.channels, sizeof(int16_t), 1, fptr);

	// write sample rate
	fwrite(&data.sample_rate, sizeof(int32_t), 1, fptr);

	// write byte rate
	fwrite(&data.byte_rate, sizeof(int32_t), 1, fptr);

	// write block align
	fwrite(&data.block_align, sizeof(int16_t), 1, fptr);

	// write # of channels
	fwrite(&data.bit_depth, sizeof(int16_t), 1, fptr);

	// write "data" chunk ID
	fwrite("data", sizeof(char), 4, fptr);

	// write number of bytes in data subchunk
	fwrite(&data.data_subchunk_size, sizeof(int32_t), 1, fptr);

	// write audio data
	fwrite(data.data, sizeof(int8_t), data.data_subchunk_size, fptr);

	// close file
	fclose(fptr);
	
	return 0;
}
