#include <stdio.h>
#include <string.h>
#include "../include/wav_read.h"
#include "../include/wav_data.h"
#include "../include/wav_write.h"

int main() {

	char filepath[256], filepath2[256];
	struct wav_data data;

	printf("this is a test of the wav_write() function.\n");
	printf("path to .wav file: ");
	scanf("%s", filepath);
	data = wav_read(filepath);
	
	printf("output file path: ");
	scanf("%s", filepath2);
	wav_write(filepath2, data);

	return 0;

}
