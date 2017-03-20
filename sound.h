/*
This is the header file for the iola_sound project
for the course Application Development at VAMK
The header file is consisted of 3 parts:
- Data structure definition
- Defined constants
- Function prototypes
*/


// Data structure definition

typedef struct{
	char ChunkID[4];
	int	ChunkSize;
	char Format[4];
	char Subchunk1ID[4];
	int Subchunk1Size;
	short int AudioFormat;
	short int NumChannels;
	int SampleRate;
	int ByteRate;
	short int BlockAlign;
	short int BitsPerSample;
	char Subchunk2ID[4];
	int Subchunk2Size;
}WAVHDR;

// Constants definition

#define SAMPLE_RATE 16000
#define PI 3.14159265359

// Function prototypes

void dispWAVHDR(WAVHDR);
void dispWAVdata(short int*);
void testTone(int, double);
