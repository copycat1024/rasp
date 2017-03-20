#include <stdio.h>
#include <math.h>
#include "sound.h"
#include "screen.h"

#define RESS 200

void print4ch(char* c){
	printf("%c%c%c%c\n",c[0],c[1],c[2],c[3]);
}

void fill4ch(char* c2, char* c1) {
	c2[0] = c1[0];
	c2[1] = c1[1];
	c2[2] = c1[2];
	c2[3] = c1[3];
}

void testTone(int f, double d){
	WAVHDR h;
	FILE* fh;
	int i;
	short int sample;
	fill4ch(h.ChunkID, "RIFF");
	fill4ch(h.Format, "WAVE");
	fill4ch(h.Subchunk1ID, "fmt ");
	fill4ch(h.Subchunk2ID, "data");
	h.Subchunk1Size = 16;
	h.AudioFormat = 1;
	h.NumChannels = 1;
	h.SampleRate = SAMPLE_RATE;
	h.BitsPerSample = 16;
	h.ByteRate = SAMPLE_RATE*h.BitsPerSample*h.NumChannels/8;
	h.BlockAlign = h.NumChannels*h.BitsPerSample/8;
	h.Subchunk2Size = h.ByteRate * d;
	h.ChunkSize = h.Subchunk2Size + 36;
	fh = fopen("testtone.wav","w");
	fwrite(&h, sizeof(h), 1, fh);
	for (i=0; i<SAMPLE_RATE*d; i++){
		sample = 32767 * sin(2*PI*f*i/SAMPLE_RATE);
		fwrite(&sample, sizeof(sample), 1 , fh);
	}
	fclose(fh);
	printf("Test tone ready!\n");
}

void dispWAVHDR(WAVHDR h){
	double duration;
#ifdef DEBUG
	printf("Chunk ID:        "); print4ch(h.ChunkID);
	printf("Chunk size:      %d\n",h.ChunkSize);
	printf("Format:          "); print4ch(h.Format);
	printf("Subchunk 1 ID:   "); print4ch(h.Subchunk1ID);
	printf("Subchunk 1 Size: %d\n",h.Subchunk1Size);
	printf("Audio Format:    %d\n",h.AudioFormat);
	printf("Num Channels:    %d\n",h.NumChannels);
	printf("Sample Rate:     %d\n",h.SampleRate);
	printf("Byte Rate:       %d\n",h.ByteRate);
	printf("Block Align:     %d\n",h.BlockAlign);
	printf("Bits Per Sample: %d\n",h.BitsPerSample);
	printf("Subchunk 2 ID:   "); print4ch(h.Subchunk2ID);
	printf("Subchunk 2 size: %d\n",h.Subchunk2Size);
#else
	duration = (double) h.Subchunk2Size/h.ByteRate;
	gotoXY(2,1); setFGcolor(CYAN);
	printf("%.3f sec",duration);
	gotoXY(22,1); setFGcolor(RED);
	printf("%d bits",h.BitsPerSample);
	gotoXY(42,1); setFGcolor(YELLOW);
	printf("%d Hz",h.SampleRate);
	resetcolor();
#endif
}

void dispWAVdata(short int* s){
	int i,j;
	double sum200, rms200;
	for (i=0; i<RESS; i++){
		sum200 = 0.0;
		for (j=0; j<SAMPLE_RATE/RESS; j++){
			sum200 += (*s)*(*s);
			s++;
		}
		rms200 = sqrt(sum200/SAMPLE_RATE*RESS);

#ifdef DEBUG
		printf("%3d: %10.2f",i,rms200);
		if (i%10==9) printf("\n");
#else
		displayBar(i+3,rms200,60,20);
#endif
	}
}