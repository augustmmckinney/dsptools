#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct wav_data {	
	int16_t audio_format, channels, block_align, bit_depth;
	int32_t chunk_size, subchunk_size, sample_rate, byte_rate, samples;
};

int main() {

	struct wav_data data;
	FILE* fptr;
	char filepath[256];
	char buffer[5];

	// retrieve path to input file, open file
	printf("full path to input file: ");
	if (scanf("%s", filepath) != 1) {
		perror("error");
		return 1;
	}
	fptr = fopen(filepath, "rb");
	if (fptr == NULL) {
		perror("error");
		return 1;
	}

	// check RIFF header
	if (fseek(fptr, 0, SEEK_SET) != 0) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return 1;
		}
		return 1;
	}
	if (fread(buffer, sizeof(char), 4, fptr) != 4) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return 1;
		}
		return 1;
	}
	buffer[4] = '\0';
	if (strcmp("RIFF", buffer) != 0) {
		printf("exiting, this file is not an RIFF file\n");
		if (fclose(fptr) != 0) {
			perror("error");
			return 1;
		}
		return 1;
	}

	// check ChunkSize
	if (fread(&data.chunk_size, sizeof(int32_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return 1;
		}
		return 1;
	}
	
	// check if the file is a WAV
	if (fread(buffer, sizeof(char), 4, fptr) != 4) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return 1;
		}
		return 1;
	}
	if (strcmp("WAVE", buffer) != 0) {
		printf("exiting, this file is not a wave file\n");
		if (fclose(fptr) != 0) {
			perror("error");
			return 1;
		}
		return 1;
	}

	// check subchunk ID, search for "fmt " subchunk	
	while (1) {
		if (fread(buffer, sizeof(char), 4, fptr) != 4) {
			perror("error");
			if (fclose(fptr) != 0) {
				perror("error");
				return 1;
			}
			return 1;
		}
		if (strcmp("fmt ", buffer) == 0) {
			break;
		}
		if (fread(&data.subchunk_size, sizeof(int32_t), 1, fptr) != 1) {
			perror("error");
			if (fclose(fptr) != 0) {
				perror("error");
				return 1;
			}	
			return 1;
		}
		if (fseek(fptr, data.subchunk_size, SEEK_CUR) != 0) {
			perror("error");
			if (fclose(fptr) != 0) {
				perror("error");
				return 1;
			}
			return 1;
		}
		
	}

	// fmt subchunk size
	if (fread(&data.subchunk_size, sizeof(int32_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return 1;
		}
		return 1;
	}

	// audio format (1 for pcm, anything else is compressed)
	if (fread(&data.audio_format, sizeof(int16_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return 1;
		}
		return 1;
	}

	// number of channels
	if (fread(&data.channels, sizeof(int16_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return 1;
		}
		return 1;
	}
	
	// sample rate
	if (fread(&data.sample_rate, sizeof(int32_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return 1;
		}
		return 1;
	}
	
	// byte rate
	if (fread(&data.byte_rate, sizeof(int32_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return 1;
		}
		return 1;
	}

	// block align (number of bytes per sample including all channels)
	if (fread(&data.block_align, sizeof(int16_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return 1;
		}
		return 1;
	}
	
	// bit depth
	if (fread(&data.bit_depth, sizeof(int16_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return 1;
		}
		return 1;
	}

	// check subchunk ID, search for "data" subchunk	
	while (1) {
		if (fread(buffer, sizeof(char), 4, fptr) != 4) {
			perror("error");
			if (fclose(fptr) != 0) {
				perror("error");
				return 1;
			}
			return 1;
		}
		if (strcmp("data", buffer) == 0) {
			break;
		}
		if (fread(&data.subchunk_size, sizeof(int32_t), 1, fptr) != 1) {
			perror("error");
			if (fclose(fptr) != 0) {
				perror("error");
				return 1;
			}
			return 1;
		}
		if (fseek(fptr, data.subchunk_size, SEEK_CUR) != 0) {
			perror("error");
			if (fclose(fptr) != 0) {
				perror("error");
				return 1;
			}
			return 1;
		}
	}
	
	// number of samples
	if (fread(&data.samples, sizeof(int32_t), 1, fptr) != 1) {
		perror("error");
		if (fclose(fptr) != 0) {
			perror("error");
			return 1;
		}
		return 1;
	}
	
	// close file
	if (fclose(fptr) != 0) {
		perror("error");
		return 1;
	}

	// return wav_data struct
	printf("audio format: %d\n", data.audio_format);
	printf("# of channels: %d\n", data.channels);
	printf("sample rate: %d\n", data.sample_rate);
	printf("byte rate: %d\n", data.byte_rate);
	printf("block align: %d\n", data.block_align);
	printf("bit depth: %d\n", data.bit_depth);
	printf("# of samples: %d\n", data.samples);

	return 0;
}
