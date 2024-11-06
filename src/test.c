#include <stdio.h>
#include "../include/wavin.h"

int main() {

	char filepath[256];
	struct wav_data data;

	printf("this is a test of the wavin() function.\n");
	printf("path to .wav file: ");
	scanf("%s", filepath);
	data = wavin(filepath);
	
	printf("audio format: %d\n", data.audio_format);
	printf("channels: %d\n", data.channels);
	printf("block align: %d\n", data.block_align);
	printf("bit_depth: %d\n", data.bit_depth);
	printf("chunk size: %d\n", data.chunk_size);
	printf("fmt subchunk size: %d\n", data.subchunk_size);
	printf("sample rate: %d\n", data.sample_rate);
	printf("byte rate: %d\n", data.byte_rate);
	printf("samples: %d\n", data.samples);

	return 0;

}





