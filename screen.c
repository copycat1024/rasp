#include "screen.h"
#include <stdio.h>

// function definition
// set height/signal strength ratio
int levelize(int i, int lim, int lev){
	return i/(lim/lev);
}

//set foreground color
void setFGcolor(int color){
	printf("\033[%d;1m", color);
	fflush(stdout);
}

//reset color
void resetcolor(void){
	printf("\033[0m");
	fflush(stdout);
}

//go to (x,y) point on the screen
void gotoXY(int x, int y){
	printf("\033[%d;%dH",y,x);
	fflush(stdout);
}

//display a bar on screen
void displayBar(int col, double rms, int lim, int reso){
	int i,j,fl = 0,l;

	int rainbow[6] = {RED,YELLOW,GREEN,CYAN,BLUE,MAGENTA};

	j = (int) rms/reso+1;

	if (j>lim) j=lim;
	for (i=0; i<j; i++){
		l = levelize(i,lim,5);
		setFGcolor(rainbow[l]);
		gotoXY(col,lim-i+2);
#ifdef UNICODE
		printf("%s", UBAR);
#else
		printf("*");
#endif
	}
	resetcolor();
	fflush(stdout);
}

//clear screen
void clrscr(){
	printf("\033[2J");
	fflush(stdout);
}
