#include <stdio.h>
#include "sound.h"
#include <signal.h>
#include <sys/wait.h>
#include "screen.h"
#include <stdlib.h>
#include <pthread.h>


void* record_sound();
void* process_sound();

// structure to pass argument to threaded process
typedef struct{
	FILE* f;
	WAVHDR* hdr;
	short int* sa;
} process_arg;

int main(int argc, char *argv[]){

	int toggle = 0;

	// thread variable
	pthread_t thread1, thread2;
	int  iret1, iret2;
	process_arg arg;
	int ret;

	while (1){
		//set up thread 1
		iret1 = pthread_create( &thread1, NULL, record_sound, (void*) &ret);
		if(iret1) {
			fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
			exit(EXIT_FAILURE);
		}
		// skip the first record becaus there is no data to sned
		if (toggle != 0) {
			//set up thread 2
			iret2 = pthread_create( &thread2, NULL, process_sound, NULL);
			if(iret2) {
				fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
				exit(EXIT_FAILURE);
			}
			pthread_join(thread2, NULL);
		} else {
			toggle = 1;
		}
		// wait for the recording to finish
		pthread_join(thread1, NULL);
		//copy recorded data to prepare for the next recording
		system("cp data.wav data1.wav");
		//check if ^C was pressed
		if (WIFSIGNALED(ret) && WTERMSIG(ret)==SIGINT) {
			clrscr();
			break;
		}
	}
	return 0;
}

//function to read sound data and process
void* process_sound(void* arg){
	FILE* f;
	WAVHDR hdr;
	short int sa[SAMPLE_RATE];
	f = fopen("data1.wav", "r");
	// read file header
	fread(&hdr,sizeof(hdr),1,f);
	dispWAVHDR(hdr);
	//read file data to display it on screen and send to server
	fread(sa, sizeof(short int), SAMPLE_RATE, f);
	dispWAVdata(sa,"iolaPi");
	fclose(f);
}

//function to record sound
void* record_sound(void* arg){
	clrscr();
	int ret, *ar;
	// run command to record
	ret = system("arecord -q -r16000 -c1 -d1 -f S16_LE data.wav");
	ar = (int*) arg;
	*ar=ret;
}
