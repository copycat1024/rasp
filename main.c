#include <stdio.h>
#include "sound.h"
#include <signal.h>
#include <sys/wait.h>
#include "screen.h"
#include <stdlib.h>

int main(int argc, char *argv[]){
	WAVHDR hdr;
	FILE* f;
	char c;
	short int sa[SAMPLE_RATE];
	int ret;

/*	if (argc<2) {
		printf("Usage: %s wav_file\n",argv[0]);
		return -1;
	}
	f = fopen(argv[1], "r");
	if (f == NULL) {
		printf("Cannnot open wav file %s\n", argv[1]);
		return -1;
	} */

	while (1){
		gotoXY(1,1);
		ret = system("arecord -q -r16000 -c1 -d1 -f S16_LE data.wav");
		if (WIFSIGNALED(ret) && WTERMSIG(ret)==SIGINT) {
			clrscr();
			break;
		}
#ifndef DEBUG
	    clrscr();
#endif
		f = fopen("data.wav", "r");
		fread(&hdr,sizeof(hdr),1,f);
		dispWAVHDR(hdr);
		fread(&sa, sizeof(short int), SAMPLE_RATE, f);
		dispWAVdata(sa);
		fclose(f);
	}


/*	printf("Do you want to generate a testone? (y for yes, others for no)");
	scanf("%c",&c);
	if (c=='y') testTone(1000, 5); */

	return 0;
}
