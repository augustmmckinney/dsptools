#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct wav_data {	
	int16_t audio_format, channels, block_align, bit_depth;
	int32_t chunk_size, subchunk_size, sample_rate, byte_rate, samples;
};

int main() {

	struct wav_data data;
	FILE* fptr;
	char filepath[100];
	char buffer[5];

	// retrieve path to input file, open file
	printf("full path to input file: ");
	scanf("%s", filepath);
	fptr = fopen(filepath, "rb");
	if (fptr == NULL) {
		printf("exiting, the file has not opened successfully\n");
		fclose(fptr);
		exit(1);
	}

	// check RIFF header
	fseek(fptr, 0, SEEK_SET);
	fread(buffer, sizeof(char), 4, fptr);
	buffer[4] = '\0';
	if (strcmp("RIFF", buffer) != 0) {
		printf("exiting, this file is not an RIFF file\n");
		fclose(fptr);
		exit(1);
	}

	// check ChunkSize
	fread(&data.chunk_size, sizeof(int32_t), 1, fptr);
	
	// check if the file is a WAV
	fread(buffer, sizeof(char), 4, fptr);
	if (strcmp("WAVE", buffer) != 0) {
		printf("exiting, this file is not a wave file\n");
		fclose(fptr);
		exit(1);
	}

	// check subchunk ID, search for "fmt " subchunk
	fread(buffer, sizeof(char), 4, fptr);
	while (strcmp("fmt ", buffer) != 0) {
		fread(&data.subchunk_size, sizeof(int32_t), 1, fptr);
		fseek(fptr, data.subchunk_size, SEEK_CUR);
		fread(buffer, sizeof(char), 4, fptr);
	}

	// fmt subchunk size
	fread(&data.subchunk_size, sizeof(int32_t), 1, fptr);

	// audio format (1 for pcm, anything else is compressed)
	fread(&data.audio_format, sizeof(int16_t), 1, fptr);

	// number of channels
	fread(&data.channels, sizeof(int16_t), 1, fptr);
	
	// sample rate
	fread(&data.sample_rate, sizeof(int32_t), 1, fptr);
	
	// byte rate
	fread(&data.byte_rate, sizeof(int32_t), 1, fptr);
	
	// block align (number of bytes per sample including all channels)
	fread(&data.block_align, sizeof(int16_t), 1, fptr);
	
	// bit depth
	fread(&data.bit_depth, sizeof(int16_t), 1, fptr);

	// check for extra parameters

	// check subchunk ID, search for "data" subchunk
	fread(buffer, sizeof(char), 4, fptr);
	while (strcmp("data", buffer) != 0) {
		fread(&data.subchunk_size, sizeof(int32_t), 1, fptr);
		fseek(fptr, data.subchunk_size, SEEK_CUR);
		fread(buffer, sizeof(char), 4, fptr);
	}
	
	// number of sample
	fread(&data.samples, sizeof(int32_t), 1, fptr);

	printf("%s\n", buffer);
	printf("%d\n", data.subchunk_size);
	printf("%d\n", data.audio_format);
	printf("%d\n", data.channels);
	printf("%d\n", data.sample_rate);
	printf("%d\n", data.byte_rate);
	printf("%d\n", data.block_align);
	printf("%d\n", data.bit_depth);
	printf("%d\n", data.samples);

	return 0;
}
