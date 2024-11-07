#include <stdio.h>
#include <string.h>
#include "../include/wav_read.h"
#include "../include/wav_data.h"
#include "../include/wav_write.h"

int main() {

	char filepath[256], filepath2[256];
	struct wav_data data;
	float m;

	printf("this program modifies the sample rate of a .wav file.\n");
	printf("path to .wav file: ");
	scanf("%s", filepath);
	data = wav_read(filepath);

	// mess with stuff
	printf("sample rate multiplier: ");
	scanf("%f", &m);
	data.sample_rate *= m;
	
	printf("output file path: ");
	scanf("%s", filepath2);
	wav_write(filepath2, data);

	return 0;

}
