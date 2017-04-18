#include <stdio.h>
#include "sound.h"
#include <signal.h>
#include <sys/wait.h>
#include "screen.h"
#include <stdlib.h>
#include <pthread.h>


void* record_sound();
void* process_sound();

typedef struct{
	FILE* f;
	WAVHDR* hdr;
	short int* sa;
} process_arg;

int main(int argc, char *argv[]){

	int toggle = 0;
	pthread_t thread1, thread2;
	int  iret1, iret2;
	process_arg arg;
	int ret;

	while (1){
		iret1 = pthread_create( &thread1, NULL, record_sound, (void*) &ret);
		if(iret1) {
			fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
			exit(EXIT_FAILURE);
		}
		if (toggle != 0) {
			iret2 = pthread_create( &thread2, NULL, process_sound, NULL);
			if(iret2) {
				fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
				exit(EXIT_FAILURE);
			}
			pthread_join(thread2, NULL);
		} else {
			toggle = 1;
		}
		pthread_join(thread1, NULL);
		system("cp data.wav data1.wav");
		if (WIFSIGNALED(ret) && WTERMSIG(ret)==SIGINT) {
			clrscr();
			break;
		}

	}
	return 0;
}

void* process_sound(void* arg){
	FILE* f;
	WAVHDR hdr;
	short int sa[SAMPLE_RATE];
	f = fopen("data1.wav", "r");
	fread(&hdr,sizeof(hdr),1,f);
	dispWAVHDR(hdr);
	fread(sa, sizeof(short int), SAMPLE_RATE, f);
	dispWAVdata(sa,"iolaPi");
	fclose(f);
}

void* record_sound(void* arg){
	clrscr();
	int ret, *ar;
	ret = system("arecord -q -r16000 -c1 -d1 -f S16_LE data.wav");
	ar = (int*) arg;
	*ar=ret;
}
