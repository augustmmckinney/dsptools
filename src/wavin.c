#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../include/wavin.h"

struct wav_data wavin(char* filepath) {

	struct wav_data data;
	FILE* fptr;
	char buffer[5];

	// retrieve path to input file, open file	
	fptr = fopen(filepath, "rb");
	if (fptr == NULL) {
		perror("error");
		return data;
	}

	// check RIFF header
	if (fseek(fptr, 0, SEEK_SET) != 0) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}
	if (fread(buffer, sizeof(char), 4, fptr) != 4) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}
	buffer[4] = '\0';
	if (strcmp("RIFF", buffer) != 0) {
		printf("exiting, this file is not an RIFF file\n");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}

	// check ChunkSize
	if (fread(&data.chunk_size, sizeof(int32_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}
	
	// check if the file is a WAV
	if (fread(buffer, sizeof(char), 4, fptr) != 4) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}
	if (strcmp("WAVE", buffer) != 0) {
		printf("exiting, this file is not a wave file\n");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}

	// check subchunk ID, search for "fmt " subchunk	
	while (1) {
		if (fread(buffer, sizeof(char), 4, fptr) != 4) {
			perror("error");
			if (fclose(fptr) != 0) {
				perror("error");
				return data;
			}
			return data;
		}
		if (strcmp("fmt ", buffer) == 0) {
			break;
		}
		if (fread(&data.subchunk_size, sizeof(int32_t), 1, fptr) != 1) {
			perror("error");
			if (fclose(fptr) != 0) {
				perror("error");
				return data;
			}	
			return data;
		}
		if (fseek(fptr, data.subchunk_size, SEEK_CUR) != 0) {
			perror("error");
			if (fclose(fptr) != 0) {
				perror("error");
				return data;
			}
			return data;
		}
		
	}

	// fmt subchunk size
	if (fread(&data.subchunk_size, sizeof(int32_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}

	// audio format (1 for pcm, anything else is compressed)
	if (fread(&data.audio_format, sizeof(int16_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}

	// number of channels
	if (fread(&data.channels, sizeof(int16_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}
	
	// sample rate
	if (fread(&data.sample_rate, sizeof(int32_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}
	
	// byte rate
	if (fread(&data.byte_rate, sizeof(int32_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}

	// block align (number of bytes per sample including all channels)
	if (fread(&data.block_align, sizeof(int16_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}
	
	// bit depth
	if (fread(&data.bit_depth, sizeof(int16_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}

	// check subchunk ID, search for "data" subchunk	
	while (1) {
		if (fread(buffer, sizeof(char), 4, fptr) != 4) {
			perror("error");
			if (fclose(fptr) != 0) {
				perror("error");
				return data;
			}
			return data;
		}
		if (strcmp("data", buffer) == 0) {
			break;
		}
		if (fread(&data.subchunk_size, sizeof(int32_t), 1, fptr) != 1) {
			perror("error");
			if (fclose(fptr) != 0) {
				perror("error");
				return data;
			}
			return data;
		}
		if (fseek(fptr, data.subchunk_size, SEEK_CUR) != 0) {
			perror("error");
			if (fclose(fptr) != 0) {
				perror("error");
				return data;
			}
			return data;
		}
	}
	
	// number of samples
	if (fread(&data.samples, sizeof(int32_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}
	
	// close file
	if (fclose(fptr) != 0) {
		perror("error");
		return data;
	}

	return data;
}
