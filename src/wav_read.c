#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../include/wav_read.h"
#include "../include/wav_data.h"

struct wav_data wav_read(char* filepath) {

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

	// read ChunkSize
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
		if (fread(&data.fmt_subchunk_size, sizeof(int32_t), 1, fptr) != 1) {
			perror("error");
			if (fclose(fptr) != 0) {
				perror("error");
				return data;
			}	
			return data;
		}
		if (fseek(fptr, data.fmt_subchunk_size, SEEK_CUR) != 0) {
			perror("error");
			if (fclose(fptr) != 0) {
				perror("error");
				return data;
			}
			return data;
		}
		
	}

	// read fmt subchunk size
	if (fread(&data.fmt_subchunk_size, sizeof(int32_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}

	// read audio format (1 for pcm, anything else is compressed)
	if (fread(&data.audio_format, sizeof(int16_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}

	// read number of channels
	if (fread(&data.channels, sizeof(int16_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}
	
	// read sample rate
	if (fread(&data.sample_rate, sizeof(int32_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}
	
	// read byte rate
	if (fread(&data.byte_rate, sizeof(int32_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}

	// read block align (number of bytes per sample including all channels)
	if (fread(&data.block_align, sizeof(int16_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}
	
	// read bit depth
	if (fread(&data.bit_depth, sizeof(int16_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}

	// read check subchunk ID, search for "data" subchunk	
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
		if (fread(&data.data_subchunk_size, sizeof(int32_t), 1, fptr) != 1) {
			perror("error");
			if (fclose(fptr) != 0) {
				perror("error");
				return data;
			}
			return data;
		}
		if (fseek(fptr, data.data_subchunk_size, SEEK_CUR) != 0) {
			perror("error");
			if (fclose(fptr) != 0) {
				perror("error");
				return data;
			}
			return data;
		}
	}
	
	// read number of bytes in the audio data
	if (fread(&data.data_subchunk_size, sizeof(int32_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return data;
		}
		return data;
	}
	
	// read audio data
	data.data = (int8_t*)malloc(data.data_subchunk_size);
	fread(data.data, sizeof(int8_t), data.data_subchunk_size, fptr);

	// close file
	if (fclose(fptr) != 0) {
		perror("error");
		return data;
	}

	return data;
}
